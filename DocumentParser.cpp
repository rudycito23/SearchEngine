//
// Created by rrluc on 4/13/2022.
//

#include "DocumentParser.h"

DocumentParser::DocumentParser(string fileName) {
    // declare the document object
    rapidjson::Document doc;

    // initialize the input file
    ifstream streamy (fileName);

    // put the whole file's data into wholeFile
    string wholeFile;
    string temp;
    while(getline(streamy,temp)) {
        wholeFile += temp;
    }
    streamy.close ();
    // call parse on the string
    doc.Parse (wholeFile.c_str());          // covert the whole file to const char*
    // make sure the parsing worked
    if (doc.IsObject ()) cout << "ITS AN OBJECT" << endl << endl;
    // loop over all the values of array
    for (auto &v : doc["entities"]["persons"].GetArray ()) {
        cout << "Person(s): " <<  v["name"].GetString() << endl;        // prints Person's name
    }
    for (auto &v : doc["entities"]["organizations"].GetArray ()) {
        cout << "Organization(s): " <<  v["name"].GetString() << endl;      // prints Organization's name
    }
    string wordsFromBlog = doc["text"].GetString();
        cout << "Words: " << wordsFromBlog << endl;         // prints the words from the actual blog
    parser(wordsFromBlog);
    cout << " " << endl;
    for (auto word : blogWords) {
        cout << word << endl;
    }
}

void DocumentParser::parser(string splitWords) {            // parser function
    string space_delimiter = " ";           // space is the delimiter
    size_t length = 0;     // size_t assures the position will never be negative
    while ((length = splitWords.find(space_delimiter)) != string::npos) {
        //currentWord is the first character encountered and its length which ends when encountering a space
        string currentWord = splitWords.substr(0, length);
        string lowerCaseLetters = "";
        for (auto& character : currentWord) {       // convert strings to lower case
            character = tolower(character);
            if ((character >= 'a') && (character <= 'z')) {
                lowerCaseLetters = lowerCaseLetters + character;    // include only characters from a-z
            }
        }
        if ((!lowerCaseLetters.empty()) && !isStopWord(lowerCaseLetters)) {     // if the currentWord is not a stop word
            Porter2Stemmer::stem(lowerCaseLetters);      // remove any stemming from the word
            // blogWords.push_back(lowerCaseLetters);          // push the currentWord into the blogWords vector
            // if pass AVLTree here, pass by reference
            // TODO - don't hard code the file
            indexTree.insertNode(lowerCaseLetters).emplace_back("blogs_0000001.json");
        }
        splitWords.erase(0, length + space_delimiter.length());
    }
}

bool DocumentParser::isStopWord(string currentWord) {
    ifstream keywordFile("stopWords.txt");     // read the file
    if (!keywordFile.is_open()) {
        cout << "Could not open file.";
    }
    string stopWord;     // stop word
    while (getline(keywordFile, stopWord)) {
        // needing to remove '\r' because I don't know what or why that keeps popping up
        // it's preventing the comparison between currentWord and stopWord
        stopWord.erase(remove(stopWord.begin(), stopWord.end(), '\r'), stopWord.end());
        if (currentWord == stopWord) {      // if currentWord == stopWord
            keywordFile.close();
            return true;        // return true
        }
    }
    keywordFile.close();
    return false;
}