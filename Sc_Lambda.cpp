//
// Created by peter on 16.12.17.
//

#include "Sc_Lambda.h"

namespace Crisp {

    Sc_Lambda::Sc_Lambda() : Sc_Value(PROC) {

    }

    Sc_Value* Sc_Lambda::eval(Scope *parent) {
        return this;
    }

    Sc_Value* Sc_Lambda::apply(Scope *scope, Sc_Cons *args) {
        Scope *context = new Scope(scope);

        Sc_Cons *start = params;
        Sc_Cons *argv = args;

        if (args->length() != params->length()) {
            delete context;
            throw std::runtime_error("Argument mismatch");
        }

        while (start) {
            Sc_Reference *ref = (Sc_Reference *) start->getCar();

            if (ref->getType() != REF) {
                delete context;
                throw std::runtime_error("Invalid syntax");
            }

            context->assign(ref->getName(), argv->getCar());

            start = (Sc_Cons *) start->getCdr();
            argv = (Sc_Cons *) argv->getCdr();
        }

        Sc_Value *val = body->eval(context);
        delete context;
        return val;
    }

    void Sc_Lambda::setParams(Sc_Cons *params) {
        this->params = params;
    }

    void Sc_Lambda::setBody(Sc_Expresssion *body) {
        this->body = body;
    }

    void* Sc_Lambda::operator new(size_t size) {
        return GC::getInstance().GC_alloc(size);
    }

    void Sc_Lambda::operator delete(void *p){
        GC::getInstance().GC_free((Sc_Value *) p);
    }

    void Sc_Lambda::toString(std::ostream &out) const {
        out << "#<procedure>";
    }
}