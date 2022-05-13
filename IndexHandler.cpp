//
// Created by rrluc on 4/9/2022.
//

#include "IndexHandler.h"

IndexHandler::IndexHandler() {  // empty constructor

}
void IndexHandler::insertWord(string word, string doc) {
    invertedFileWordIndex.insertNode(word).emplace_back(doc);       // insert the word and document into AVLTree
}

void IndexHandler::traverse() {     // print the tree inorder
    invertedFileWordIndex.inOrderTraversal();
}

vector<string> IndexHandler::findWord(string findWordKey) {      // find the key within the AVLTree
    string lowerCaseLetters;
    for (auto& character : findWordKey) {       // convert strings to lower case
        character = tolower(character);
        if ((character >= 'a') && (character <= 'z')) {
            lowerCaseLetters = lowerCaseLetters + character;    // include only characters from a-z
        }
    }
    Porter2Stemmer::stem(lowerCaseLetters);
    return invertedFileWordIndex.findNode(lowerCaseLetters);     // return the key
}

vector<string> IndexHandler::findOrg(string findOrgKey) {
    string lowerCaseLetters;
    for (auto& character : findOrgKey) {       // convert strings to lower case
        character = tolower(character);
        if ((character >= 'a') && (character <= 'z')) {
            lowerCaseLetters = lowerCaseLetters + character;    // include only characters from a-z
        }
    }
    Porter2Stemmer::stem(lowerCaseLetters);
    return invertedFileOrgIndex.findNode(lowerCaseLetters);
}

vector<string> IndexHandler::findPerson(string findPersonKey) {
    string lowerCaseLetters;
    for (auto& character : findPersonKey) {       // convert strings to lower case
        character = tolower(character);
        if ((character >= 'a') && (character <= 'z')) {
            lowerCaseLetters = lowerCaseLetters + character;    // include only characters from a-z
        }
    }
    Porter2Stemmer::stem(lowerCaseLetters);
    return invertedFilePersonIndex.findNode(lowerCaseLetters);
}

void IndexHandler::insertPerson(string person, string doc) {
    invertedFilePersonIndex.insertNode(person).emplace_back(doc);
}

void IndexHandler::insertOrg(string org, string doc) {
    invertedFileOrgIndex.insertNode(org).emplace_back(doc);
}

int IndexHandler::getWordSize() {
    return invertedFileWordIndex.getWordCounter();
}

int IndexHandler::getOrgSize() {
    return invertedFileOrgIndex.getWordCounter();
}

int IndexHandler::getPersonSize() {
    return invertedFilePersonIndex.getWordCounter();
}