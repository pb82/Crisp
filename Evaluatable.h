//
// Created by peter on 16.12.17.
//

#ifndef CRISP_EVALUATABLE_H
#define CRISP_EVALUATABLE_H

#include "Sc_Value.h"
#include "Scope.h"

namespace Crisp {

    class Evaluatable {
    public:
        Evaluatable() = default;
        virtual ~Evaluatable() = default;
        virtual Sc_Value *eval(Scope *parent) = 0;
    };

}

#endif //CRISP_EVALUATABLE_H
