cmake_minimum_required(VERSION 3.12)
project(cpp_decorators_tests)

set(CMAKE_CXX_STANDARD 17)

include_directories(one_header_file tests)

add_executable(cpp_decorators_tests 
tests/tests_main.cpp 
tests/cpp_decorator_basic_tests.cpp 
tests/cpp_multiple_decorators_tests.cpp
one_header_file/cpp_decorators.h
tests/catch.hpp)

set(dir ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(EXECUTABLE_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)