//
// Created by peter on 20.12.17.
//

#ifndef CRISP_PARSER_H
#define CRISP_PARSER_H


#include "Sc_Expresssion.h"
#include "Tokenizer.h"
#include "VM.h"

namespace Crisp {

    class Parser {
    public:
        Parser(std::string source);
        Evaluatable *start();
    private:
        Tokenizer tokenizer;
        TokenProvider tp;

        Sc_Expresssion *parseExpression();
        void parseArguments(Sc_Cons *form);
        Sc_Value *parseRefOrCallable();
    };

}

#endif //CRISP_PARSER_H
