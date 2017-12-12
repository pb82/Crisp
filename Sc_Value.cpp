//
// Created by peter on 12.12.17.
//

#include "Sc_Value.h"

namespace Crisp {

    Sc_Type Sc_Value::getType() const {
        return this->type;
    }

    bool Sc_Value::marked() const {
        return this->GC_mark;
    }

    void Sc_Value::mark(bool val) {
        this->GC_mark = val;
    }

}