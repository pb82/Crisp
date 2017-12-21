//
// Created by peter on 15.12.17.
//

#include "VM.h"

namespace Crisp {

    VM::VM() : global(new Scope(nullptr)) {
        GC::getInstance().setGlobalScope(global);
        define("identity", VM::identity);
        define("gc/stats", VM::gc_stats);
        define("+", VM::add);
    }

    VM::~VM() {
        delete global;
    }

    Scope* const VM::getScope() const {
        return global;
    }

    void VM::define(const char *name, ExtFn fn) {
        Sc_External_Proc *proc = new Sc_External_Proc(fn);
        global->assign(name, proc);
    }

    // cdr(a . (b . (c . nil)))     => (b . (c . nil))
    Sc_Value *VM::cdr(Sc_Cons *cell) {
        return cell->getCdr();
    }

    // cons(a, b)                   => (a . b)
    // cons(a, cons(b))             => (a . (b . nil))
    Sc_Cons *VM::cons(Sc_Value *car, Sc_Value *cdr) {
        return new Sc_Cons(car, cdr);
    }

}