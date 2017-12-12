//
// Created by peter on 12.12.17.
//

#ifndef CRISP_STDLIB_H
#define CRISP_STDLIB_H

#include <vector>

#include "Sc_Value.h"
#include "Sc_Cons.h"

namespace Crisp {
    Sc_Cons *cons(Sc_Value *car, Sc_Value *cdr) {
        return new Sc_Cons(car, cdr);
    }

    template <class ...T> Sc_Cons *list(T ... t) {
        std::vector<Sc_Value *> items = {t...};
    }
}

#endif //CRISP_STDLIB_H
