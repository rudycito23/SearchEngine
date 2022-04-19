//
// Created by rrluc on 4/9/2022.
//

#ifndef INC_22S_FINAL_PROJ_INDEXHANDLER_H
#define INC_22S_FINAL_PROJ_INDEXHANDLER_H

#include <iostream>
#include <string>
#include "AVLTree.h"
#include <vector>

using std::string;
using std::cout;
using std::cin;
using std::vector;
using std::endl;

class IndexHandler {
private:
    AVLTree<string, vector<string>> indexTree;

public:
    IndexHandler();
    // create an insert function that stores the word and doc into my AVLTree
    void insert(string, string);
    void traverse();
    vector<string> find(const string&);

};

#endif //INC_22S_FINAL_PROJ_INDEXHANDLER_H