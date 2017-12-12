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
        for (Sc_Value *memory : allocated) {
            free(memory);
        }
    }

    Sc_Value* GC::GC_alloc(size_t size) {
        Sc_Value *memory = (Sc_Value *) malloc(size);
        allocated.push_back(memory);
        return memory;
    }

    void GC::GC_free(Sc_Value *memory) {
        auto it = std::find(allocated.begin(), allocated.end(), memory);
        if (it == allocated.end()) {
            // tried to free a pointer to a region of memory that was
            // not allocated by this pool. Ignore this.
            return;
        } else {
            auto index = std::distance(allocated.begin(), it);
            allocated.erase(allocated.begin() + index);
            free(memory);
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
        for (Sc_Value *memory : allocated) {
            if (memory && !memory->marked()) {
                GC_free(memory);
            }
        }

        global->traverseMark(false);
    }

    void GC::setGlobalScope(Scope *scope) {
        global = scope;
    }
}