//
// Created by peter on 12.12.17.
//

#ifndef CRISP_SC_NUMBER_H
#define CRISP_SC_NUMBER_H

#include <gmp.h>

#include "Sc_Value.h"
#include "GC.h"

namespace Crisp {

    class Sc_Number : public Sc_Value {
    public:
        Sc_Number(signed long int value);
        ~Sc_Number();

        void toString(std::ostream &out) const;
        void *operator new (size_t size);
        void operator delete(void *p);
    private:
        mpz_t value;
    };

}


#endif //CRISP_SC_NUMBER_H
