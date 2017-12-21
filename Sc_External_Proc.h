//
// Created by peter on 15.12.17.
//

#ifndef CRISP_SC_EXTERNAL_PROC_H
#define CRISP_SC_EXTERNAL_PROC_H

#include "Callable.h"
#include "Scope.h"
#include "Sc_Value.h"
#include "GC.h"

namespace Crisp {

    class Sc_External_Proc : public Callable {
    public:
        Sc_External_Proc(ExtFn fn);
        ~Sc_External_Proc();

        Sc_Value *apply(Scope *scope, Sc_Cons *args);

        void toString(std::ostream &out) const;
        void *operator new (size_t size);
        void operator delete(void *p);
    private:
        ExtFn fn;
    };

}

#endif //CRISP_SC_EXTERNAL_PROC_H
