cmake_minimum_required(VERSION 3.16.3)
project(22s_final_proj)

set(CMAKE_CXX_STANDARD 14)

add_executable(22s_final_proj main.cpp catch_setup.cpp InvertedFileIndex.cpp InvertedFileIndex.h IndexHandler.cpp IndexHandler.h AVLTree.h DocumentParser.cpp DocumentParser.h porter2_stemmer.h porter2_stemmer.cpp)
