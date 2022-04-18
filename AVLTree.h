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
    int max(int a, int b) {
        return (a > b) ? a : b;
    }
    // calculate the height
    int getHeight(const AVLNode<key, value> *&aNode) {
        if (aNode == nullptr) {     // if there is no node, then the height is -1
            return -1;
        }
        else {
            return aNode->height;       // returns the height of the node
        }
    }
    // create a new AVLNode
    AVLNode<key, value> *newNode(key kData, value vData) {
        AVLNode<key, value> *newNode = new AVLNode<key, value>;       // allocate memory
        newNode->keyData = kData;          // insert data into keyData pointer
        newNode->leftPtr = nullptr;        // left pointer will be null
        newNode->rightPtr = nullptr;       // right pointer will be null
        newNode->height = 1;               // height of the new node is now 1
        return newNode;
    }
    // rotate right
    AVLNode<key, value> *rotateRight(AVLNode<key, value> *rotateR) {
        AVLNode<key, value> *xPtr = rotateR->leftPtr;
        AVLNode<key, value> *yPtr = xPtr->rightPtr;
        xPtr->rightPtr = rotateR;
        rotateR->leftPtr = yPtr;
        rotateR->height = max(getHeight(rotateR->leftPtr), getHeight(rotateR->rightPtr)) + 1;
        xPtr->height = max(getHeight(xPtr->leftPtr), getHeight(xPtr->rightPtr)) + 1;
        return xPtr;
    }
    // rotate left
    AVLNode<key, value> *rotateLeft(AVLNode<key, value> *rotateL) {
        AVLNode<key, value> *xPtr = rotateL->rightPtr;
        AVLNode<key, value> *yPtr = xPtr->leftPtr;
        xPtr->leftPtr = rotateL;
        rotateL->rightPtr = yPtr;
        rotateL->height = max(getHeight(rotateL->leftPtr), getHeight(rotateL->rightPtr)) + 1;
        xPtr->height = max(getHeight(yPtr->leftPtr), getHeight(yPtr->rightPtr) + 1);
        return xPtr;
    }
    // get the balance factor of each node (difference between the height of the left subtree minus right subtree)
    int getBalanceFactor(AVLNode<key, value> *checkNode) {
        if (checkNode == nullptr) {
            return 0;
        }
        return getHeight(checkNode->leftPtr) - getHeight(checkNode->rightPtr);
    }

    // perform inorder traversal
    void inOrderTraversal() {
        printInOrder(rootPtr);
    }
    // perform inorder traversal of AVLTree
    void printInOrder(AVLNode<key, value> *ptr) {
        if (ptr != nullptr) {
            printInOrder(ptr->leftPtr);
            cout << ptr->valData << " ";
            printInOrder(ptr->rightPtr);
        }
    }
};


#endif //INC_22S_FINAL_PROJ_AVLTREE_H
