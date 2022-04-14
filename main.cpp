#include <iostream>
#include "DocumentParser.h"

int main() {
    string word = "baked";
    Porter2Stemmer::stem(word);
    cout << word << endl << endl;


    DocumentParser file("blogs_0000001.json");


    return 0;
}
