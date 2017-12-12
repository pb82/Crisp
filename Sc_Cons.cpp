//
// Created by peter on 12.12.17.
//

#include "Sc_Cons.h"

namespace Crisp {
    Sc_Cons::Sc_Cons(Sc_Value *car, Sc_Value *cdr) : Sc_Value(CELL), car(car), cdr(cdr) {

    }

    void* Sc_Cons::operator new(size_t size) {
        Sc_Value *memory = GC::getInstance().GC_alloc(size);
        return memory;
    }

    void Sc_Cons::operator delete(void *p){
        GC::getInstance().GC_free((Sc_Value *) p);
    }

    Sc_Value* Sc_Cons::getCar() const {
        return car;
    }

    Sc_Value* Sc_Cons::getCdr() const {
        return cdr;
    }

    void Sc_Cons::toString(std::ostream &out) const {
        out << "(";
        car->toString(out);
        out << " . ";
        if (cdr) {
            cdr->toString(out);
        } else {
            out << "nil";
        }
    }

}