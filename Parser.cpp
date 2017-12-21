//
// Created by peter on 20.12.17.
//

#include "Parser.h"

namespace Crisp {

    Parser::Parser(std::string source) {
        tokenizer.reset();
        tp.init(tokenizer.run(source));
    }

    void Parser::parseArguments(Sc_Cons *form) {
        Sc_Cons *current = form;

        while (tp.hasNext()) {
            if (tp.peek().type == TT_RPAREN) {
                break;
            }

            Sc_Value *n = nullptr;
            if (tp.peek().type == TT_LPAREN) {
                n = parseExpression();
            } else {
                Token t = tp.next();
                n = new Sc_Number(t.value);
            }

            Sc_Cons *cdr = new Sc_Cons(n, nullptr);
            current->setCdr(cdr);
            current = cdr;
        }
    }

    Sc_Value* Parser::parseRefOrCallable() {
        Token id = tp.expect(TT_IDENTIFIER);
        Sc_Reference *ref = new Sc_Reference(id.value);
        return ref;
    }

    Sc_Expresssion* Parser::parseExpression() {
        tp.expect(TT_LPAREN);
        Sc_Value *fn = parseRefOrCallable();
        Sc_Cons *form = new Sc_Cons(fn, nullptr);
        parseArguments(form);
        tp.expect(TT_RPAREN);

        return new Sc_Expresssion(form);
    }

    Evaluatable* Parser::start() {
        Sc_Expresssion *ex = parseExpression();
        return ex;
    }

}