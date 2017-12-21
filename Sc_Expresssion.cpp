//
// Created by peter on 16.12.17.
//

#include "Sc_Expresssion.h"

namespace Crisp {

    Sc_Expresssion::Sc_Expresssion(Sc_Cons *start) : Sc_Value(SEXPR), start(start) {

    }

    Sc_Expresssion::~Sc_Expresssion() {
        if (start) {
            delete start;
        }
    }

    Sc_Value *Sc_Expresssion::eval(Scope *parent) {
        Sc_Value *tmp = start->getCar();
        Sc_Cons *args = (Sc_Cons *) start->getCdr();

        Callable *fn = nullptr;

        if (tmp->getType() == PROC) {
            fn = (Callable *) tmp;
        } else if (tmp->getType() == REF) {
            Sc_Reference *ref = (Sc_Reference *) tmp;
            Sc_Value *val = parent->lookup(ref->getName());
            if (val->getType() != PROC) {
                throw std::runtime_error("Cannot call non-proc");
            } else {
                fn = (Callable *) val;
            }
        } else {
            throw std::runtime_error("Cannot call non-proc");
        }

        if (!args) {
            return fn->apply(parent, nullptr);
        }

        if (args->getType() != CELL) {
            throw std::runtime_error("Argument error");
        }

        Sc_Cons *mappedArgs = args->map([parent](Sc_Value *val) {
            if (val->getType() == SEXPR || val->getType() == REF) {
                Evaluatable *e = dynamic_cast<Evaluatable *>(val);
                Scope *context = new Scope(parent);
                Sc_Value *result = e->eval(context);
                delete context;
                return result;
            } else {
                return val;
            }
        });

        Sc_Value *result = fn->apply(parent, mappedArgs);
        return result;
    }

    void *Sc_Expresssion::operator new(size_t size) {
        Sc_Value *memory = GC::getInstance().GC_alloc(size);
        return memory;
    }

    void Sc_Expresssion::operator delete(void *p) {
        GC::getInstance().GC_free((Sc_Value *) p);
    }

    void Sc_Expresssion::toString(std::ostream &out) const {
        start->toString(out);
    }

}