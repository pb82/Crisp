//
// Created by peter on 19.12.17.
//

#ifndef CRISP_TOKENIZER_H
#define CRISP_TOKENIZER_H

#include <string>
#include <vector>
#include <sstream>
#include <ostream>
#include <ctype.h>

#include "Errors.h"

namespace Crisp {

    enum TokenType {
        TT_NUMBER,
        TT_IDENTIFIER,
        TT_LPAREN,
        TT_RPAREN,
        TT_QUOTE,
        TT_POUND,
        TT_TRUE,
        TT_FALSE,
        TT_STRING
    };

    class Token {
    public:
        Token(TokenType type, std::string value, int line, int pos);
        Token(TokenType type, int line, int pos);

        ~Token() = default;

        TokenType type;
        std::string value;
        int line;
        int position;

        static std::string stringify(TokenType type);
    };

    class TokenProvider {
    public:
        TokenProvider();

        void init(std::vector<Token> tokens);
        Token& peek();
        Token next();
        bool hasNext();
        bool has(TokenType type);
        Token expect(TokenType type);

    private:
        std::vector<Token> tokens;
        int index;
        int length;
    };

    class Tokenizer {
    public:
        Tokenizer();
        void toString(std::ostream &out) const;
        std::vector<Token> run(std::string source);
        void reset();
    private:
        bool hasNext() const;
        char peek() const;
        char next();
        void unnext();

        void readString();
        bool readNumber();
        void readIdentifier();
        bool readBoolean();

        void commit(TokenType type);

        bool validIdentifierChar(char c) const;
        bool validNumberChar(char c) const;
        bool isNewline(char c) const;
        bool isWhitespace( char c) const;

        int index;
        int line;
        int position;

        std::string source;
        std::ostringstream currentId;
        std::vector<Token> tokens;
    };

}



#endif //CRISP_TOKENIZER_H
