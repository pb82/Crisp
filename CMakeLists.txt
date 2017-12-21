cmake_minimum_required(VERSION 3.6)
project(Crisp)

set(CMAKE_CXX_STANDARD 11)

add_executable(Crisp main.cpp Sc_Value.cpp Sc_Value.h Sc_Number.cpp Sc_Number.h GC.cpp GC.h Sc_Cons.cpp Sc_Cons.h Scope.cpp Scope.h VM.cpp VM.h Callable.h Sc_External_Proc.cpp Sc_External_Proc.h Sc_Reference.cpp Sc_Reference.h Evaluatable.h Sc_Expresssion.cpp Sc_Expresssion.h Sc_Lambda.cpp Sc_Lambda.h Tokenizer.cpp Tokenizer.h Parser.cpp Parser.h Errors.h Errors.cpp)
target_link_libraries(Crisp gmp readline)