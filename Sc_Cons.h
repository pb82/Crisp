//
// Created by peter on 12.12.17.
//

#ifndef CRISP_SC_CONS_H
#define CRISP_SC_CONS_H

#include <functional>

#include "Sc_Value.h"
#include "GC.h"

namespace Crisp {

    class Sc_Cons : public Sc_Value {
    public:
        Sc_Cons();
        Sc_Cons(Sc_Value *car, Sc_Value *cdr);

        ~Sc_Cons() = default;

        void toString(std::ostream &out) const;
        void *operator new (size_t size);
        void operator delete(void *p);

        Sc_Value *getCar() const;
        Sc_Value *getCdr() const;
        void setCar(Sc_Value *val);
        void setCdr(Sc_Value *val);

        int length() const;

        Sc_Cons *map(std::function<Sc_Value *(Sc_Value *)> fn) const;

        template<typename T> void reduce(T *acc, std::function<void(T *acc, Sc_Value *item)> fn) const {
            const Sc_Cons *start = this;

            while (start) {
                fn(acc, start->getCar());

                if (!start->getCdr()) {
                    break;
                }

                if (start->getCdr()->getType() != CELL) {
                    throw std::runtime_error("Reduce over non-iterable");
                }

                start = (Sc_Cons *) start->getCdr();
            }
        }

    private:
        Sc_Value *car;
        Sc_Value *cdr;
    };

}

#endif //CRISP_SC_CONS_H
