//
// Created by peter on 12.12.17.
//

#include "GC.h"

namespace Crisp {

    GC& GC::getInstance() {
        static GC instance;
        return instance;
    }

    GC::~GC() {
        for (auto const &memory : allocated) {
            free(memory.first);
        }
    }

    Sc_Value* GC::GC_alloc(size_t size) {
        Sc_Value *memory = (Sc_Value *) malloc(size);
        allocated[memory] = size;

        // Update stats
        currentAlloc += size;
        updateMax();

        return memory;
    }

    void GC::GC_free(Sc_Value *memory) {
        if (allocated.find(memory) != allocated.end()) {
            // Update stats
            size_t size = allocated[memory];
            currentAlloc -= size;
            updateMax();

            // Free
            allocated.erase(memory);
            free(memory);
        } else {
            // Can't free memory not known to the garbage collector.
            // Ignore such requests.
            return;
        }
    }

    void GC::GC_collect() {
        if (global) {
            mark();
            sweep();
        }
    }

    void GC::mark() {
        global->traverseMark(true);
    }

    void GC::sweep() {
        for (auto const &memory : allocated) {
            Sc_Value *pointer = memory.first;
            if (pointer && !pointer->marked()) {
                GC_free(pointer);
            }
        }

        // Reset the mark on all surviving entries
        global->traverseMark(false);
    }

    void GC::setGlobalScope(Scope *scope) {
        global = scope;
    }

    void GC::updateMax() {
        maxAlloc = currentAlloc > maxAlloc ? currentAlloc : maxAlloc;
    }

    int GC::getCurrentAlloc() const {
        return currentAlloc;
    }

    int GC::getMaxAlloc() const {
        return maxAlloc;
    }
}