//
// Created by peter on 12.12.17.
//

#include "Sc_Number.h"

namespace Crisp {

    Sc_Number::Sc_Number(signed long int val) : Sc_Value(NUMBER) {
        mpz_init(value);
        mpz_set_si(value, val);
    }

    Sc_Number::~Sc_Number() {
        mpz_clear(value);
    }

    void* Sc_Number::operator new(size_t size) {
        Sc_Value *memory = GC::getInstance().GC_alloc(size);
        return memory;
    }

    void Sc_Number::operator delete(void *p){
        GC::getInstance().GC_free((Sc_Value *) p);
    }

    void Sc_Number::toString(std::ostream &out) const {
        out << mpz_get_str(nullptr, 0, value);
    }

}