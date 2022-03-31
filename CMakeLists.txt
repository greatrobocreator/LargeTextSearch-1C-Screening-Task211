cmake_minimum_required(VERSION 3.17)
project(LargeTextSearch_1C_Screening_Task211)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Ofast)

add_executable(Main main.cpp Automaton/SuffixAutomaton.cpp Automaton/SuffixAutomaton.h NodesManager.cpp NodesManager.h)
