//
// Created by peter on 15.12.17.
//

#ifndef CRISP_CALLABLE_H
#define CRISP_CALLABLE_H

#include <functional>

#include "Sc_Value.h"
#include "Sc_Cons.h"
#include "Scope.h"

namespace Crisp {

    typedef std::function<Sc_Value *(Scope *, Sc_Cons *)> ExtFn;

    class Callable : public Sc_Value {
    public:
        Callable() : Sc_Value(PROC) { }
        virtual Sc_Value *apply(Scope *scope, Sc_Cons *args) = 0;
    };

}

#endif //CRISP_CALLABLE_H
