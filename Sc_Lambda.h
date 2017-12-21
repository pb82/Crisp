//
// Created by peter on 16.12.17.
//

#ifndef CRISP_SC_LAMBDA_H
#define CRISP_SC_LAMBDA_H

#include "Callable.h"
#include "Evaluatable.h"
#include "Sc_Value.h"
#include "Sc_Expresssion.h"
#include "GC.h"

namespace Crisp {

    class Sc_Lambda : public Sc_Value, public Evaluatable {
    public:
        Sc_Lambda();

        Sc_Value *apply(Scope *scope, Sc_Cons *args);
        Sc_Value *eval(Scope *parent);

        void setParams(Sc_Cons *params);
        void setBody(Sc_Expresssion *body);

        void toString(std::ostream &out) const;
        void *operator new (size_t size);
        void operator delete(void *p);

    private:
        Sc_Cons *params;
        Sc_Expresssion *body;
    };

}

#endif //CRISP_SC_LAMBDA_H
