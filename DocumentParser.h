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
#include <filesystem>
#include <utility>

using std::cout;
using std::cin;
using std::string;
using std::ifstream;
using std::ostream;
using std::remove;
using std::vector;
using std::pair;
using std::map;
using std::pair;
using std::endl;
namespace fs = std::filesystem;

class DocumentParser {
private:
    map<string, int> stopWords;

public:
    DocumentParser();
    void parse(const string&, IndexHandler&);
    void parseFolder(const string&, IndexHandler&);
    bool isStopWord(const string&);
    void readStopWords();
    void printTree(IndexHandler&);
    vector<pair<string, int>> rankRelevancy(const vector<string> &, vector<string> &);
    vector<string> findDocuments(string&, IndexHandler&);
};

#endif //INC_22S_FINAL_PROJ_DOCUMENTPARSER_H