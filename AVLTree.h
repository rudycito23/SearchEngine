//
// Created by rrluc on 4/9/2022.
//

#ifndef INC_22S_FINAL_PROJ_AVLTREE_H
#define INC_22S_FINAL_PROJ_AVLTREE_H

#include "InvertedFileIndex.h"

template <typename key, typename value>       // double template

struct AVLNode {
    AVLNode <key, value> *leftPtr;
    AVLNode <key, value> *rightPtr;
    key keyData;
    value valData;
    int height;

    // overloaded constructor
    AVLNode(const key& kData, value& vData, AVLNode<key, value> *argLeftPtr, AVLNode<key, value> *argRightPtr, int h = 0) {
        keyData = kData;
        valData = vData;
        leftPtr = argLeftPtr;
        rightPtr = argRightPtr;
        height = h;
    }
    AVLNode() {         // default constructor
        height = -1;
        leftPtr = nullptr;
        rightPtr = nullptr;
    }
    AVLNode(const AVLNode <key, value> &arg) {      // copy constructor
        leftPtr = arg.leftPtr;
        rightPtr = arg.rightPtr;
    }
};

template<typename key, typename value>

class AVLTree {
private:
    AVLNode<key, value> *rootPtr{nullptr};
    value& privateInsertNode(const key& kData, AVLNode<key, value> *currentNode) {}

public:
    // calling .insertNode in main, will then trigger calling privateInsertNode which will
    // traverse the tree recursively
    value& insertNode(const key& kData) {
        privateInsertNode(kData, rootPtr);  // return privateInsertNode
    }
    int getHeight(const AVLNode<key, value> *&aNode) {
        if (aNode == nullptr) {     // if there is no node, then the height is -1
            return -1;
        }
        else {
            return aNode->height;       // returns the height of the node
        }
    }
    


};


#endif //INC_22S_FINAL_PROJ_AVLTREE_H
