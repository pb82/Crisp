//
// Created by peter on 21.12.17.
//

#ifndef CRISP_ERRORS_H
#define CRISP_ERRORS_H

#include <stdexcept>
#include <sstream>

namespace Crisp { namespace Errors {

    extern std::runtime_error createParseError(int line, int position, char found);
    extern std::runtime_error createParseError(int line, int position, std::string found, std::string expected);
    extern std::runtime_error createParseError(std::string expected);

} }

#endif //CRISP_ERRORS_H
