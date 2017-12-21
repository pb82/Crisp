//
// Created by peter on 16.12.17.
//

#ifndef CRISP_SC_EXPRESSSION_H
#define CRISP_SC_EXPRESSSION_H

#include "Sc_Value.h"
#include "Sc_Cons.h"
#include "Sc_Reference.h"
#include "Scope.h"
#include "GC.h"
#include "Evaluatable.h"
#include "Callable.h"

namespace Crisp {

    class Sc_Expresssion : public Sc_Value, public Evaluatable {
    public:
        Sc_Expresssion(Sc_Cons *start);
        ~Sc_Expresssion();

        void toString(std::ostream &out) const;
        void *operator new (size_t size);
        void operator delete(void *p);

        Sc_Value *eval(Scope *parent);

    private:
        Sc_Cons *start;
    };

}

#endif //CRISP_SC_EXPRESSSION_H
