#include "Errors.h"

namespace Crisp {
    namespace Errors {

        std::runtime_error createParseError(int line, int position, char found) {
            std::stringstream ss;
            ss << "Unexpected token: `";
            ss << found;
            ss << "` at position ";
            ss << line;
            ss << ":";
            ss << position;
            return std::runtime_error(ss.str());
        }

        std::runtime_error createParseError(int line, int position, std::string found, std::string expected) {
            std::stringstream ss;
            ss << "Unexpected token: `";
            ss << found;
            ss << "` at position ";
            ss << line;
            ss << ":";
            ss << position;
            ss << " (expected `";
            ss << expected;
            ss << "`)";
            return std::runtime_error(ss.str());
        }

        std::runtime_error createParseError(std::string expected) {
            std::stringstream ss;
            ss << "Expected `";
            ss << expected;
            ss << "` but end of stream reached";
            return std::runtime_error(ss.str());
        }

    }
}