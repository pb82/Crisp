//
// Created by peter on 12.12.17.
//

#include "Sc_Number.h"

namespace Crisp {

    Sc_Number::Sc_Number(signed long int val) : Sc_Value(NUMBER) {
        mpz_init(value);
        mpz_set_si(value, val);
    }

    Sc_Number::Sc_Number(mpz_t val) : Sc_Value(NUMBER) {
        mpz_init(value);
        mpz_set(value, val);
    }

    Sc_Number::Sc_Number(std::string val) : Sc_Value(NUMBER) {
        mpz_init(value);
        mpz_set_str(value, val.c_str(), 0);
    }

    Sc_Number::~Sc_Number() {
        mpz_clear(value);
    }

    Sc_Value* Sc_Number::eval(Scope *parent) {
        return this;
    }

    Sc_Number* Sc_Number::abs() {
        mpz_t result;
        mpz_init(result);
        mpz_abs(result, value);
        return new Sc_Number(result);
    }

    Sc_Number* Sc_Number::operator+=(Sc_Number *rhs) {
        mpz_add(value, value, rhs->value);
        return this;
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