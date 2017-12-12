#define CATCH_CONFIG_MAIN
#include "catch.h"

#include <string>
#include <sstream>
#include <iostream>

#include "Sc_Number.h"
#include "Sc_Cons.h"
#include "Scope.h"
#include "Stdlib.h"

using namespace Crisp;

TEST_CASE( "Basic types behavior Sc_Number#toString", "[Sc_Number]" ) {
    Sc_Number a(1);

    std::stringstream ss;
    a.toString(ss);

    REQUIRE(ss.str().compare("1") == 0);
}

TEST_CASE( "Memory management", "[Sc_Number]" ) {

    Scope *global = new Scope(nullptr);
    Scope *secondary = new Scope(global);

    Sc_Number *a = new Sc_Number(1);

    secondary->assign("a", a);

    GC::getInstance().setGlobalScope(global);

    delete secondary;
    GC::getInstance().GC_collect();

    Sc_Cons *l = list(a, a);

    std::cout << "Memory pool success" << std::endl;
}
