cmake_minimum_required(VERSION 3.12)
project(proc)

set(CMAKE_CXX_STANDARD 14)

add_executable(proc main.cpp stack.h stack.cpp cpu.h comp.h cpu.cpp comp.cpp)