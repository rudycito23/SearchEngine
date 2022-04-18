//
// Created by rrluc on 4/13/2022.
//

#ifndef INC_22S_FINAL_PROJ_DOCUMENTPARSER_H
#define INC_22S_FINAL_PROJ_DOCUMENTPARSER_H

#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include "include/rapidjson/document.h"
#include "Porter2_Stemmer.h"
#include <dirent.h>
#include "IndexHandler.h"
#include <map>

using std::cout;
using std::cin;
using std::string;
using std::ifstream;
using std::ostream;
using std::remove;
using std::vector;
using std::pair;
using std::map;
using std::endl;

class DocumentParser {
private:
    IndexHandler handler;
    map<string, int> stopWords;

public:
    DocumentParser();
    void parse(const string&);
    bool isStopWord(const string&);
    void readStopWords();
    void printTree();

};


#endif //INC_22S_FINAL_PROJ_DOCUMENTPARSER_H
