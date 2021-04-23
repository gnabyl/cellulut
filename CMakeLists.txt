cmake_minimum_required(VERSION 3.17)
project(lo21 C CXX)
set(CMAKE_CXX_STANDARD 14)
add_executable(lo21 automata.cpp automata.h automataManager.h automataManager.cpp)
