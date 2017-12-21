#include "Sc_Number.h"
#include "Sc_Cons.h"
#include "Parser.h"

#include <readline/readline.h>
#include <readline/history.h>

using namespace Crisp;

void readLine(VM &vm) {
    char *line = nullptr;
    line = readline("> ");

    if (line && *line) {
        Parser parser(line);
        add_history(line);

        Evaluatable *e = parser.start();
        Sc_Value *result = e->eval(vm.getScope());
        result->toString(std::cout);
        std::cout << std::endl;
        GC::getInstance().GC_collect();
    }
}

int main() {
    VM vm;

    while (true) {
        readLine(vm);
    }
}