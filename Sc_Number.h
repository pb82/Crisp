//
// Created by peter on 12.12.17.
//

#ifndef CRISP_SC_NUMBER_H
#define CRISP_SC_NUMBER_H

#include <gmp.h>

#include "Sc_Value.h"
#include "Evaluatable.h"
#include "GC.h"
#include "Scope.h"

namespace Crisp {

    class Sc_Number : public Sc_Value, public Evaluatable {
    public:
        explicit Sc_Number(signed long int val);
        explicit Sc_Number(std::string val);
        explicit Sc_Number(mpz_t val);

        ~Sc_Number();

        Sc_Number *abs();
        Sc_Value *eval(Scope *parent);

        void toString(std::ostream &out) const;
        void *operator new (size_t size);
        void operator delete(void *p);
        Sc_Number *operator+=(Sc_Number *rhs);

    private:
        mpz_t value;
    };

}


#endif //CRISP_SC_NUMBER_H
