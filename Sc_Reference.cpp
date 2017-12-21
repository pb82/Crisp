//
// Created by peter on 16.12.17.
//

#include "Sc_Reference.h"

namespace Crisp {

    Sc_Reference::Sc_Reference(const char *name) : Sc_Value(REF), refName(name) {
        // empty
    }

    Sc_Reference::Sc_Reference(std::string name) : Sc_Value(REF), refName(name) {
        // empty
    }

    Sc_Reference::~Sc_Reference() {
        // empty
    }

    const std::string& Sc_Reference::getName() const {
        return refName;
    }

    Sc_Value* Sc_Reference::eval(Scope *parent) {
        return parent->lookup(refName);
    }

    void* Sc_Reference::operator new(size_t size) {
        Sc_Value *memory = GC::getInstance().GC_alloc(size);
        return memory;
    }

    void Sc_Reference::operator delete(void *p){
        GC::getInstance().GC_free((Sc_Value *) p);
    }

    void Sc_Reference::toString(std::ostream &out) const {
        out << refName;
    }

}