cmake_minimum_required(VERSION 3.16.3)
project(22s_final_proj)

set(CMAKE_CXX_STANDARD 17)

add_executable(22s_final_proj main.cpp catch_setup.cpp IndexHandler.cpp IndexHandler.h AVLTree.h DocumentParser.cpp DocumentParser.h Porter2_Stemmer.h Porter2_Stemmer.cpp QueryProcessor.cpp QueryProcessor.h SearchEngine.cpp SearchEngine.h)
