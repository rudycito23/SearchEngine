#include <iostream>
#include "DocumentParser.h"
#include "AVLTree.h"

int main() {
//    string word = "baked";
//    Porter2Stemmer::stem(word);
//    cout << word << endl << endl;


    // DocumentParser file("blogs_0000001.json");
    AVLTree<int, int> intTree;
    cout << "Enter 10 integers: \n";

    // insert 10 integers to AVLTree
    for (int i{0}; i < 10; ++i) {
        int value{0};
        cin >> value;
        intTree.insertNode(value);
    }
    intTree.inOrderTraversal();


    return 0;
}
