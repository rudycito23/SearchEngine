//
// Created by rrluc on 5/1/2022.
//

#include "SearchEngine.h"

SearchEngine::SearchEngine() {

}
SearchEngine::SearchEngine(string fileName) {
    this->fileName = fileName;          // this = private data member
}

void SearchEngine::parseData() {
    parser.parseFolder(fileName, handler);      // calls the parseFolder function and passes in fileName & handler
}

void SearchEngine::printMenu() {
    string search;
    while (search != "stop"){
        cout << "Welcome! My name is A R I A, your search engine. " << endl << endl;
        cout << "What do you wish to find? " << endl;
        cout << "Type \"stop\" to quit. " << endl;

        getline(cin ,search);

        processor.processQuery(search, handler);
    }
}