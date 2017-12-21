//
// Created by peter on 15.12.17.
//

#include "Sc_External_Proc.h"

namespace Crisp {

    Sc_External_Proc::Sc_External_Proc(ExtFn fn) : Callable(), fn(fn) {

    }

    Sc_External_Proc::~Sc_External_Proc() {

    }

    Sc_Value* Sc_External_Proc::apply(Scope *scope, Sc_Cons *args) {
        return fn(scope, args);
    }

    void* Sc_External_Proc::operator new(size_t size) {
        return GC::getInstance().GC_alloc(size);
    }

    void Sc_External_Proc::operator delete(void *p){
        GC::getInstance().GC_free((Sc_Value *) p);
    }

    void Sc_External_Proc::toString(std::ostream &out) const {
        out << "#<procedure>";
    }
}