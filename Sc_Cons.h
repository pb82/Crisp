//
// Created by peter on 12.12.17.
//

#ifndef CRISP_SC_CONS_H
#define CRISP_SC_CONS_H

#include "Sc_Value.h"
#include "GC.h"

namespace Crisp {

    class Sc_Cons : public Sc_Value {
    public:
        Sc_Cons(Sc_Value *car, Sc_Value *cdr);
        ~Sc_Cons() = default;

        void toString(std::ostream &out) const;
        void *operator new (size_t size);
        void operator delete(void *p);

        Sc_Value *getCar() const;
        Sc_Value *getCdr() const;
    private:
        Sc_Value *car;
        Sc_Value *cdr;
    };

}

#endif //CRISP_SC_CONS_H
