//
// Created by rrluc on 4/9/2022.
//

#ifndef INC_22S_FINAL_PROJ_INDEXHANDLER_H
#define INC_22S_FINAL_PROJ_INDEXHANDLER_H

#include <iostream>
#include <string>
#include "AVLTree.h"
#include <vector>
#include "Porter2_Stemmer.h"

using std::string;
using std::cout;
using std::cin;
using std::vector;
using std::endl;

class IndexHandler {
private:
    AVLTree<string, vector<string>> invertedFileWordIndex;      // this is the inverted file index for Words
    AVLTree<string, vector<string>> invertedFileOrgIndex;       // this is the inverted file index for ORG
    AVLTree<string, vector<string>> invertedFilePersonIndex;    // this is the inverted file index for PERSON

public:
    IndexHandler();
    // create an insert function that stores the word and doc into my AVLTree
    void insertWord(string, string);
    void insertPerson(string, string);
    void insertOrg(string, string);
    void traverse();
    vector<string> findWord(string);
    vector<string> findOrg(string);
    vector<string> findPerson(string);
};

#endif //INC_22S_FINAL_PROJ_INDEXHANDLER_H