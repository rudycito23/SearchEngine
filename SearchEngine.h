//
// Created by rrluc on 5/1/2022.
//

#ifndef INC_22S_FINAL_PROJ_SEARCHENGINE_H
#define INC_22S_FINAL_PROJ_SEARCHENGINE_H

#include "IndexHandler.h"
#include "DocumentParser.h"
#include "QueryProcessor.h"
#include <string>

class SearchEngine {
private:
    IndexHandler handler;
    DocumentParser parser;
    QueryProcessor processor;
    string fileName;

public:
    SearchEngine();
    SearchEngine(string);
    void printMenu();

    void parseData();
};
#endif //INC_22S_FINAL_PROJ_SEARCHENGINE_H