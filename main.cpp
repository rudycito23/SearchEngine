#include <iostream>
#include "DocumentParser.h"
#include <chrono>
#include "IndexHandler.h"

int main(int argc, char** argv) {
    if (argc == 1) {        // argc = argument count
        cout << "Error: No file inserted." << endl;
        return  -1;
    }
    else {
        DocumentParser docParser;
        auto start = std::chrono::high_resolution_clock::now();
        docParser.parseFolder(argv[1]);
        auto end = std::chrono::high_resolution_clock::now();
        auto time = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
        cout << time << " seconds" << endl;
        string keyName = argv[2];
        vector<string> results = docParser.findDocuments(keyName);
        cout << "Your word appears in the following files: " << endl;
        for (auto const &x:results) {
            cout << x << endl;
        }
    }
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
