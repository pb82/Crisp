//
// Created by peter on 12.12.17.
//

#include "Sc_Cons.h"

namespace Crisp {
    Sc_Cons::Sc_Cons(Sc_Value *car, Sc_Value *cdr) : Sc_Value(CELL), car(car), cdr(cdr) {
        // empty
    }

    Sc_Cons::Sc_Cons() : Sc_Value(CELL), car(nullptr), cdr(nullptr) {
        // empty. It's important to initialize car and cdr with nullptr,
        // otherwise they would point to random memory addresses
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

    void Sc_Cons::setCar(Sc_Value *val) {
        car = val;
    }

    void Sc_Cons::setCdr(Sc_Value *val) {
        cdr = val;
    }

    int Sc_Cons::length() const {
        int length = 0;

        const Sc_Cons *start = this;
        while (start) {
            length++;
            Sc_Value *next = start->getCdr();
            if (next == nullptr) {
                break;
            } else if (next->getType() == CELL) {
                start = (Sc_Cons *) next;
                continue;
            } else {
                length++;
                break;
            }
        }

        return length;
    }

    Sc_Cons* Sc_Cons::map(std::function<Sc_Value *(Sc_Value *)> fn) const {
        const Sc_Cons *start = this;
        Sc_Cons* result = new Sc_Cons;
        Sc_Cons* mapped = result;

        while (start) {
            mapped->setCar(fn(start->getCar()));

            if (!start->getCdr()) {
                mapped->setCdr(nullptr);
                break;
            }

            if (start->getCdr()->getType() != CELL) {
                throw std::runtime_error("Map over non-iterable");
            }

            mapped->setCdr(new Sc_Cons);
            mapped = (Sc_Cons *) mapped->getCdr();

            start = (Sc_Cons *) start->getCdr();
        }

        return result;
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
        out << ")";
    }

}