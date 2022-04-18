#include <iostream>
#include "DocumentParser.h"
#include "IndexHandler.h"

int main(int argc, char** argv) {
    if (argc == 1) {        // argc = argument count
        cout << "Error: No file inserted." << endl;
        return  -1;
    }
    else {
        // https://www.delftstack.com/howto/cpp/how-to-get-list-of-files-in-a-directory-cpp/
        DIR *dir; struct dirent *diread;
        DocumentParser docParser;
        if ((dir = opendir(argv[1])) != nullptr) {
            while ((diread = readdir(dir)) != nullptr) {
                string file = string(diread->d_name);
                if ((file != "..") && file != ".") {
                    string fileName = string(argv[1]) + "/" + string(diread->d_name);
                    docParser.parse(fileName);
                }
            }
            closedir (dir);
        } else {
            perror ("opendir");
            return EXIT_FAILURE;
        }
        docParser.printTree();
        return EXIT_SUCCESS;
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
