//
// Created by rrluc on 4/9/2022.
//

#include "IndexHandler.h"

IndexHandler::IndexHandler() {  // empty constructor

}
void IndexHandler::insert(string word,  string doc) {
    indexTree.insertNode(word).emplace_back(doc);       // insert the word and document into AVLTree
}

void IndexHandler::traverse() {     // print the tree inorder
    indexTree.inOrderTraversal();
}

vector<string> IndexHandler::find(const string &findKey) {
    return indexTree.findNode(findKey);
}
