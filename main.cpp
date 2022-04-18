#include <iostream>
#include "DocumentParser.h"
#include "AVLTree.h"

int main() {
//    string word = "baked";
//    Porter2Stemmer::stem(word);
//    cout << word << endl << endl;


     DocumentParser file("blogs_0000001.json");
     file.indexTree.inOrderTraversal();

    //AVLTree<int, int> intTree;

    // insert 10 integers to AVLTree
    //for (int i{0}; i < 10; ++i) {
        //int value{0};
        //cin >> value;intTree.insertNode(5);
//    intTree.insertNode(5);
//    intTree.insertNode(23);
//    intTree.insertNode(99);
//    intTree.insertNode(11);
//    intTree.insertNode(19);
//    intTree.insertNode(-1);
//    intTree.insertNode(-5);
//    //}
//    intTree.inOrderTraversal();



    return 0;
}
