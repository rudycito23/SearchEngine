//
// Created by rrluc on 4/9/2022.
//

#ifndef INC_22S_FINAL_PROJ_AVLTREE_H
#define INC_22S_FINAL_PROJ_AVLTREE_H

#include <algorithm>
#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::max;

// The key represents the searched word
// The value represents the document where the word appears
template <typename key, typename value>       // double template (key, value) pair

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
    // performs traversal of tree                            recursively
    value& privateInsertNode(const key& kData, AVLNode<key, value> *&currentNode) {
        if (currentNode == nullptr) {  // if currentNode is a leaf node *CHECK IF NULLPTR*
            currentNode = new AVLNode<key, value>(kData, nullptr, nullptr);     // leaf node
            return currentNode->valData;
        }
        else if (kData < currentNode->keyData) {        // if kData is less than currentNode's data
            // storing the value of currentNode in result variable
            value &result = privateInsertNode(kData, currentNode->leftPtr);     // climb down the tree -> go left
            balanceTree(currentNode);       // climb up the tree
            // store the value of currentNode in result variable
            return result;
        }
        else if (kData > currentNode->keyData) {        // if kData is less than currentNode's data
            // storing the value of currentNode in result variable
            value &result = privateInsertNode(kData, currentNode->rightPtr);    // climb down the tree -> go right
            balanceTree(currentNode);       // climb up the tree
            // storing the value of currentNode in result variable
            return result;
        }
        else {
            return currentNode->valData;        // if duplicate, return the currentNode's data
        }
    }
    value& privateFindNode(const key& kData, AVLNode<key, value> *&currentNode) {
        if (currentNode == nullptr) {
            cout << "Error: Word is not found." << endl;
            return rootPtr->valData;
        }
        else if (kData < currentNode->keyData) {
            return privateFindNode(kData, currentNode->leftPtr);
        }
        else if (kData > currentNode->keyData) {
            return privateFindNode(kData, currentNode->rightPtr);
        }
        else {
            return currentNode->valData;
        }
    }
    // to balance, find the difference between the height of leftPtr and rightPtr
    void balanceTree(AVLNode<key, value> *&currentNode) {
        if (currentNode == nullptr) {
            return;
        }
        // balance factor will be -1, 0, 1
        // if the height of currentNode's (leftPtr) - height of currentNode's (rightPtr) is > 1, continue
        // if the height of currentNode's (leftPtr and its leftPtr) is >= height of currentNode's (rightPtr),
        // rotate the currentNode left by calling the rotateLeft function
        if (getHeight(currentNode->leftPtr) - getHeight(currentNode->rightPtr) > 1) {
            if (getHeight(currentNode->leftPtr->leftPtr) >= getHeight(currentNode->leftPtr->rightPtr)) {
                rotateLeft(currentNode);
            }
            else {
                // double rotate left = rotating the currentNode's leftPtr right, and then rotating left
                rotateRight(currentNode->leftPtr);
                rotateLeft(currentNode);
            }
        }
        // if the height of currentNode's (rightPtr) - height of currentNode's (leftPtr) is > 1, continue
        // if height of currentNode's (rightPtr and its rightPtr) is >= height of currentNode's (rightPtr and its leftPtr),
        // then rotate the currentNode right by calling the rotateRight function
        else if (getHeight(currentNode->rightPtr) - getHeight(currentNode->leftPtr) > 1) {
            if (getHeight(currentNode->rightPtr->rightPtr) >= getHeight(currentNode->rightPtr->leftPtr)) {
                rotateRight(currentNode);
            }
            else {
                // double rotate right = rotating the currentNode's (rightPtr) left, and then rotating right
                rotateLeft(currentNode->rightPtr);
                rotateRight(currentNode);
            }
        }
        // adjust the height of the currentNode after every iteration
        currentNode->height = max(getHeight(currentNode->leftPtr), getHeight(currentNode->rightPtr)) + 1;
    }

public:
    // calling .insertNode in main, will then trigger calling privateInsertNode which will
    // traverse the tree recursively
    value& insertNode(const key& kData) {
        return privateInsertNode(kData, rootPtr);  // return privateInsertNode
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
        AVLNode<key, value> *newNode = new AVLNode<key, value>;       // allocate memory for new node
        newNode->keyData = kData;          // insert data into keyData pointer
        newNode->leftPtr = nullptr;        // left pointer will be null
        newNode->rightPtr = nullptr;       // right pointer will be null
        newNode->height = 1;               // height of the new node is now 1
        return newNode;
    }
    // rotate left
    void rotateLeft(AVLNode<key, value> *&rotateL) {
        AVLNode<key, value> *xPtr = rotateL->leftPtr;   // create a *xPtr of AVLNode type to be leftPtr
        AVLNode<key, value> *yPtr = xPtr->rightPtr;     // create a *yPtr of AVLNode type to be rightPtr
        xPtr->rightPtr = rotateL;       // xPtr's rightPtr will be rotateL pointer
        rotateL->leftPtr = yPtr;        // rotateL's leftPtr will be yPtr
        // rotateL's height = height of its leftPtr and the height of its rightPtr + 1
        rotateL->height = max(getHeight(rotateL->leftPtr), getHeight(rotateL->rightPtr)) + 1;
        // xPtr's height = height of its leftPtr and the height of rotateL + 1;
        xPtr->height = max(getHeight(xPtr->leftPtr), getHeight(rotateL)) + 1;
        rotateL = xPtr;     // rotateL is now xPtr
    }
    // rotate right
    void rotateRight(AVLNode<key, value> *&rotateR) {
        AVLNode<key, value> *xPtr = rotateR->rightPtr;      // create *xPtr of AVLNode type to be rightPtr
        AVLNode<key, value> *yPtr = xPtr->leftPtr;          // create a *yPtr of AVLNode type to be leftPtr
        xPtr->leftPtr = rotateR;        // xPtr's leftPtr will be rotateR pointer
        rotateR->rightPtr = yPtr;       // rotateR's rightPtr will be yPtr
        // rotateR's height = height of its leftPtr and the height of its rightPtr + 1
        rotateR->height = max(getHeight(rotateR->leftPtr), getHeight(rotateR->rightPtr)) + 1;
        // xPtr's height = height of rotateR and the height of rightPtr + 1;
        xPtr->height = max(getHeight(rotateR), getHeight(xPtr->rightPtr)) + 1;
        rotateR = xPtr;     // rotateR is now xPtr
    }
    // get the balance factor of each node (difference between the height of the left subtree minus right subtree)
    int getBalanceFactor(AVLNode<key, value> *checkNode) {
        if (checkNode == nullptr) {     // if checkNode equals nullptr then its zero
            return 0;
        }
        // else, (height of checkNode's leftPtr) - (height of checkNode's rightPtr) = height
        return getHeight(checkNode->leftPtr) - getHeight(checkNode->rightPtr);
    }
    value& findNode(const key& kData) {
        return privateFindNode(kData, rootPtr);
    }

    // print inorder traversal
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