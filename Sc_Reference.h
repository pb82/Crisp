//
// Created by peter on 16.12.17.
//

#ifndef CRISP_SC_REFERENCE_H
#define CRISP_SC_REFERENCE_H

#include <string>

#include "Sc_Value.h"
#include "Evaluatable.h"
#include "GC.h"

namespace Crisp {

    class Sc_Reference : public Sc_Value, public Evaluatable {
    public:
        Sc_Reference(const char *name);
        Sc_Reference(std::string name);
        ~Sc_Reference();

        const std::string &getName() const;
        Sc_Value *eval(Scope *parent);

        void toString(std::ostream &out) const;
        void *operator new (size_t size);
        void operator delete(void *p);

    private:
        std::string refName;
    };

}

#endif //CRISP_SC_REFERENCE_H
