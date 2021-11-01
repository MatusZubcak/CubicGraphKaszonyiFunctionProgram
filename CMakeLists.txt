cmake_minimum_required(VERSION 3.17)
project(CubicGraphKaszonyiFunctionProgram)

set(CMAKE_CXX_STANDARD 14)

add_executable(CubicGraphKaszonyiFunctionProgram main.cpp Tests.cpp Tests.h Edge.cpp Edge.h GraphExceptions.cpp GraphExceptions.h CubicGraph.cpp CubicGraph.h KaszonyiFunction.h KaszonyiFactorFunction.cpp KaszonyiFactorFunction.h GraphLoader.h AdjListsGraphLoader.cpp AdjListsGraphLoader.h)