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
#include "AVLTree.h"

using std::cout;
using std::cin;
using std::string;
using std::ifstream;
using std::ostream;
using std::remove;
using std::vector;
using std::endl;

class DocumentParser {
//private:
    //AVLTree<string, vector<string>> indexTree;

public:
    AVLTree<string, vector<string>> indexTree;
    std::vector<string> blogWords;

    DocumentParser(string);
    void parser(string);
    bool isStopWord(string);



};


#endif //INC_22S_FINAL_PROJ_DOCUMENTPARSER_H
