//
// Created by rrluc on 4/9/2022.
//

#ifndef INC_22S_FINAL_PROJ_AVLTREE_H
#define INC_22S_FINAL_PROJ_AVLTREE_H

#include <algorithm>
#include "InvertedFileIndex.h"

using std::max;
template <typename key, typename value>       // double template

struct AVLNode {
    AVLNode <key, value> *leftPtr;
    AVLNode <key, value> *rightPtr;
    key keyData;
    value valData;
    int height;

    // overloaded constructor
    AVLNode(const key& kData, AVLNode<key, value> *argLeftPtr, AVLNode<key, value> *argRightPtr, int h = 0) {
        keyData = kData;
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
    value& privateInsertNode(const key& kData, AVLNode<key, value> *&currentNode) {
        if (currentNode == nullptr) {  // if currentNode is a leaf node *CHECK IF NULLPTR*
            currentNode = new AVLNode<key, value>(kData, nullptr, nullptr);     // leaf node
            return currentNode->valData;
        }
        else if (kData < currentNode->keyData) {
            // storing the value of currentNode in result variable
            value &result = privateInsertNode(kData, currentNode->leftPtr);     // climb down the tree
            balanceTree(currentNode);       // climb up the tree
            return result;
        }
        else if (kData > currentNode->keyData) {
            // storing the value of currentNode in result variable
            value &result = privateInsertNode(kData, currentNode->rightPtr);    // climb down the tree
            balanceTree(currentNode);       // climb up the tree
            return result;
        }
        else {
            return currentNode->valData;
        }
            // The key represents the searched word
            // The value represents the document where the word appears
            // Utilize a key - value pair
    }
    void balanceTree(AVLNode<key, value> *&currentNode) {
        if (currentNode == nullptr) {
            return;
        }
        if (getHeight(currentNode->leftPtr) - getHeight(currentNode->rightPtr) > 1) {
            if (getHeight(currentNode->leftPtr->leftPtr) >= getHeight(currentNode->leftPtr->rightPtr)) {
                rotateLeft(currentNode);
            }
            else {
                // double rotate left
                rotateRight(currentNode->leftPtr);
                rotateLeft(currentNode);
            }
        }
        else if (getHeight(currentNode->rightPtr) - getHeight(currentNode->leftPtr) > 1) {
            if (getHeight(currentNode->rightPtr->rightPtr) >= getHeight(currentNode->rightPtr->leftPtr)) {
                rotateRight(currentNode);
            }
            else {
                // double rotate right
                rotateLeft(currentNode->rightPtr);
                rotateRight(currentNode);
            }
        }
        // adjust the height of the currentNode
        currentNode->height = max(getHeight(currentNode->leftPtr), getHeight(currentNode->rightPtr)) + 1;
    }

public:
    // calling .insertNode in main, will then trigger calling privateInsertNode which will
    // traverse the tree recursively
    value& insertNode(const key& kData) {
        privateInsertNode(kData, rootPtr);  // return privateInsertNode
    }
    // calculate the height
    int getHeight(AVLNode<key, value> *aNode) {
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
    void rotateLeft(AVLNode<key, value> *&rotateR) {
        AVLNode<key, value> *xPtr = rotateR->leftPtr;
        AVLNode<key, value> *yPtr = xPtr->rightPtr;
        xPtr->rightPtr = rotateR;
        rotateR->leftPtr = yPtr;
        rotateR->height = max(getHeight(rotateR->leftPtr), getHeight(rotateR->rightPtr)) + 1;
        xPtr->height = max(getHeight(xPtr->leftPtr), getHeight(rotateR)) + 1;
        rotateR = xPtr;
    }
    // rotate left
    void rotateRight(AVLNode<key, value> *&rotateL) {
        AVLNode<key, value> *xPtr = rotateL->rightPtr;
        AVLNode<key, value> *yPtr = xPtr->leftPtr;
        xPtr->leftPtr = rotateL;
        rotateL->rightPtr = yPtr;
        rotateL->height = max(getHeight(rotateL->leftPtr), getHeight(rotateL->rightPtr)) + 1;
        xPtr->height = max(getHeight(rotateL), getHeight(xPtr->rightPtr)) + 1;
        rotateL = xPtr;
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
            cout << ptr->keyData << " ";
            printInOrder(ptr->rightPtr);
        }
    }
};


#endif //INC_22S_FINAL_PROJ_AVLTREE_H
