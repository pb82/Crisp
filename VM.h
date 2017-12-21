//
// Created by peter on 15.12.17.
//

#ifndef CRISP_VM_H
#define CRISP_VM_H

#include <stdexcept>

#include "Scope.h"
#include "GC.h"
#include "Sc_External_Proc.h"
#include "Sc_Reference.h"
#include "Sc_Number.h"

#define SC_PROC(name) static Sc_Value *name(Scope *scope, Sc_Cons *args)

namespace Crisp {

    class VM {
    public:
        VM();
        ~VM();

        Scope * const getScope() const;
        void define(const char *name, ExtFn fn);

        template <typename T> static T *car(Sc_Cons *cell) {
            return (T *) cell->getCar();
        }

        static Sc_Value *cdr(Sc_Cons *cell);
        static Sc_Cons* cons(Sc_Value *car, Sc_Value *cdr);

        // list(a, b, c)                => (a . (b . (c . nil)))
        template <class ...T> static Sc_Cons *list(T ... t) {
            std::vector<Sc_Value *> items = {t...};

            Sc_Cons *start = new Sc_Cons();
            Sc_Cons *current = start;

            int length = items.size();

            for (int i = 0; i < length; i++) {
                current->setCar(items.at(i));

                // Another item in the list? If yes we need to allocate
                // another cons cell
                if (i + 1 < length) {
                    current->setCdr(new Sc_Cons);
                    current = (Sc_Cons *) current->getCdr();
                }
            }

            return start;
        }

        SC_PROC(identity) {
            return car<Sc_Value>(args);
        }

        SC_PROC(gc_stats) {
            Sc_Cons *result = list(
                    new Sc_Number(GC::getInstance().getCurrentAlloc()),
                    new Sc_Number(GC::getInstance().getMaxAlloc())
            );

            return result;
        }

        SC_PROC(add) {
            int len = args->length();

            if (len < 1) {
                return new Sc_Number(0L);
            }

            Sc_Number *result = new Sc_Number(0L);
            args->reduce<Sc_Number>(result, [scope, result](Sc_Number *acc, Sc_Value *item) {
                if (item->getType() != NUMBER) {
                    throw std::runtime_error("Arithmetic error");
                }

                *result += (Sc_Number *) item;
            });

            return result;
        }

    private:
        Scope *global;
    };

}

#endif //CRISP_VM_H
