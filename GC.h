//
// Created by peter on 12.12.17.
//

#ifndef CRISP_GC_H
#define CRISP_GC_H

#include <vector>
#include <map>
#include <cstdlib>
#include <algorithm>
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

        int getCurrentAlloc() const;
        int getMaxAlloc() const;
    private:
        GC() { };

        void mark();
        void sweep();
        void updateMax();

        std::map<Sc_Value *, size_t> allocated;
        Scope *global;

        int maxAlloc;
        int currentAlloc;
    };

}


#endif //CRISP_GC_H
