//
// Created by peter on 12.12.17.
//

#ifndef CRISP_GC_H
#define CRISP_GC_H

#include <vector>
#include <cstdlib>
#include <algorithm>
#include <stdexcept>
#include <iostream>

#include "Sc_Value.h"
#include "Scope.h"

namespace Crisp {

    class GC {
    public:
        static GC& getInstance();

        ~GC();

        GC(GC const&) = delete;
        void operator=(GC const&) = delete;

        Sc_Value *GC_alloc(size_t size);
        void GC_free(Sc_Value *memory);
        void GC_collect();

        void setGlobalScope(Scope *scope);
    private:
        GC() { };

        void mark();
        void sweep();

        std::vector<Sc_Value *> allocated;
        Scope *global;
    };

}


#endif //CRISP_GC_H
