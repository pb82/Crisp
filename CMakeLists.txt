cmake_minimum_required(VERSION 3.9)
project(Crisp)

set(CMAKE_CXX_STANDARD 11)

add_executable(Crisp main.cpp catch.h Sc_Value.cpp Sc_Value.h Sc_Number.cpp Sc_Number.h GC.cpp GC.h Sc_Cons.cpp Sc_Cons.h Stdlib.h Scope.cpp Scope.h)
target_link_libraries(Crisp gmp)