//
// Created by peter on 19.12.17.
//

#include "Tokenizer.h"

namespace Crisp {

    Token::Token(TokenType type, std::string value, int line, int pos)
    : type(type), value(value), line(line), position(pos) {
        // empty
    }

    Token::Token(TokenType type, int line, int pos)
            : type(type), line(line), position(pos) {
        // empty
    }

    std::string Token::stringify(TokenType type) {
        switch(type) {
            case TT_NUMBER:
                return "number";
            case TT_IDENTIFIER:
                return "identifier";
            case TT_LPAREN:
                return "(";
            case TT_RPAREN:
                return ")";
            case TT_QUOTE:
                return "'";
            case TT_POUND:
                return "#";
            case TT_TRUE:
                return "boolean";
            case TT_FALSE:
                return "boolean";
            case TT_STRING:
                return "string";
            default:
                return "<unknown>";
        }
    }

    Tokenizer::Tokenizer() : index(0), line(1), position(0) {
        //empty
    }

    TokenProvider::TokenProvider() {
        index = 0;
    }

    void TokenProvider::init(std::vector<Token> tokens) {
        this->tokens = tokens;
        length = tokens.size();
    }

    Token& TokenProvider::peek() {
        return tokens.at(index);
    }

    Token TokenProvider::next() {
        return tokens.at(index++);
    }

    bool TokenProvider::hasNext() {
        return index < length;
    }

    bool TokenProvider::has(TokenType type) {
        return hasNext() && tokens.at(index + 1).type == type;
    }

    Token TokenProvider::expect(TokenType type) {
        if (!hasNext()) {
            throw Errors::createParseError(Token::stringify(type));
        }

        Token n = next();
        if (n.type != type) {
            throw Errors::createParseError(n.line, n.position, n.value, Token::stringify(type));
        }

        return n;
    }

    std::vector<Token> Tokenizer::run(std::string source) {
        this->source = source;

        while (hasNext())  {
            char c = next();

            if (isNewline(c)) {
                line++;
                position = 0;
                continue;
            }

            if (isWhitespace(c)) {
                continue;
            }

            if (c == '(') {
                commit(TT_LPAREN);
                continue;
            }

            if (c == ')') {
                commit(TT_RPAREN);
                continue;
            }

            if (c == '\'') {
                commit(TT_QUOTE);
                continue;
            }

            if (c == '#') {
                if(readBoolean()) {
                    continue;
                } else {
                    commit(TT_POUND);
                    continue;
                }
            }

            if (c == '\"') {
                readString();
                continue;
            }

            unnext();
            int snapshotIndex = index;
            int snapshotPosition = position;
            if (!readNumber()) {
                index = snapshotIndex;
                position = snapshotPosition;
                readIdentifier();
            }
        }

        return tokens;
    }

    bool Tokenizer::readBoolean() {
        char c = next();
        if (c == 't') {
            commit(TT_TRUE);
            return true;
        } else if (c == 'f') {
            commit(TT_FALSE);
            return true;
        }

        unnext();
        return false;
    }

    bool Tokenizer::readNumber() {
        bool success = false;

        while (true) {
            if (!hasNext() || isWhitespace(peek())) {
                break;
            }

            if (!validIdentifierChar(peek())) {
                break;
            }

            char c = next();
            if (validNumberChar(c)) {
                success = true;
                currentId << c;
            } else {
                success = false;
                break;
            }
        }

        if (success) {
            commit(TT_NUMBER);
        }

        return success;
    }

    void Tokenizer::readIdentifier() {
        bool success = false;

        while (true) {
            if (!hasNext() || isWhitespace(peek())) {
                break;
            }

            if (!validIdentifierChar(peek())) {
                break;
            }

            char c = next();
            if (validIdentifierChar(c)) {
                currentId << c;
                success = true;
            } else {
                throw Errors::createParseError(line, position, c);
            }
        }

        if (success) {
            commit(TT_IDENTIFIER);
        }
    }

    void Tokenizer::readString() {
        while (hasNext() && peek() != '\"') {
            char c = next();

            // Backslash escape
            if (c == 92) {
                currentId << next();
            } else {
                currentId << c;
            }
        }

        commit(TT_STRING);
        next(); // consume "
    }

    bool Tokenizer::isNewline(char c) const {
        return (c == 10 || c == 12 || c == 13);
    }

    bool Tokenizer::isWhitespace(char c) const {
        return isspace(c) || isNewline(c);
    }

    bool Tokenizer::hasNext() const {
        return index < source.length();
    }

    char Tokenizer::peek() const {
        return source.at(index);
    }

    char Tokenizer::next() {
        position++;
        return source.at(index++);
    }

    void Tokenizer::unnext() {
        position-=1;
        index-=1;
    }

    void Tokenizer::commit(TokenType type) {
        if (type == TT_NUMBER || type == TT_IDENTIFIER || type == TT_STRING) {
            std::string id = currentId.str();
            tokens.push_back(Token(type, id, line, position - id.length()));
            currentId.str("");
        } else {
            tokens.push_back(Token(type, line, position));
        }
    }

    bool Tokenizer::validIdentifierChar(char c) const {
        return
                (c >= 65 && c <= 90)    ||
                (c >= 97 && c <= 122)   ||
                (c >= 48 && c <= 57)    ||
                c == '+' ||
                c == '-' ||
                c == '.' ||
                c == '*' ||
                c == '/' ||
                c == '<' ||
                c == '=' ||
                c == '>' ||
                c == '!' ||
                c == '?' ||
                c == ':' ||
                c == '$' ||
                c == '%' ||
                c == '_' ||
                c == '&' ||
                c == '~' ||
                c == '^';
    }

    bool Tokenizer ::validNumberChar(char c) const {
        return (c >= 48 && c <= 57);
    }

    void Tokenizer::toString(std::ostream &out) const {
        for (Token const&t : tokens) {
            out << t.type << ": " << t.value << " (" << t.line << ":" << t.position << ")" << std::endl;
        }
    }

    void Tokenizer::reset() {
        this->position = 0;
        this->index = 0;
        this->line = 1;
        this->tokens.clear();
        this->currentId.str("");
        this->source = "";
    }
}