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

void SearchEngine::executeSearch(const string &search) {
    vector<string> result = processor.processQuery(search, handler);
    for (int i = 0; i < result.size(); ++i) {
        cout << result[i] << endl;
    }
}

//void SearchEngine::printMenu() {
//    cout << "Welcome to  A R I A " << endl << endl;
//    cout << "What do you wish to find? " << endl;
//
//    string search;
//    cin >> search;
//    if (search = )
//
//}