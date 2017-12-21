//
// Created by peter on 12.12.17.
//

#ifndef CRISP_SCOPE_H
#define CRISP_SCOPE_H

#include <map>
#include <vector>
#include <string>
#include <algorithm>

#include "Sc_Value.h"

namespace Crisp {

    class Scope {
    public:
        Scope(Scope *parent);
        ~Scope();

        Sc_Value *lookup(std::string key);

        void assign(const char *key, Sc_Value *value);
        void assign(std::string key, Sc_Value *value);


        void traverseMark(bool val);
        void registerChild(Scope *childScope);
        void deregisterChild(Scope *childScope);
    private:
        std::map<std::string, Sc_Value *> bindings;
        std::vector<Scope *> childScopes;

        Scope *parent = nullptr;
    };

}

#endif //CRISP_SCOPE_H
