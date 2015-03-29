cmake_minimum_required(VERSION 3.1.0)
project(sudokubot)

add_executable(sudokubot main.cpp puzzle.cpp square.cpp)

set_property(TARGET sudokubot PROPERTY CXX_STANDARD 11)
set_property(TARGET sudokubot PROPERTY CXX_STANDARD_REQUIRED on)

install(TARGETS sudokubot RUNTIME DESTINATION bin)
