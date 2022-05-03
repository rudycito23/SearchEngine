//
// Created by rrluc on 4/13/2022.
//

#include "DocumentParser.h"

DocumentParser::DocumentParser() {
    readStopWords();
}

void DocumentParser::parse(const string &fileName, IndexHandler &handler) {     // parser function
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
     for (auto &v : doc["persons"].GetArray ()) {
         string kDataPerson = v.GetObject().begin()->value.GetString();     // convert Persons to strings
         for (int i = 0; i < kDataPerson.size(); ++i) {
             kDataPerson[i] = tolower(kDataPerson[i]);      // convert Person to lowercase letters
         }
         handler.insertPerson(kDataPerson, fileName);       // inserting to AVLTree for Persons
     }
     for (auto &v : doc["organizations"].GetArray ()) {
         string kDataOrg = v.GetObject().begin()->value.GetString();        // convert Orgs to strings
         for (int i = 0; i < kDataOrg.size(); ++i) {
             kDataOrg[i] = tolower(kDataOrg[i]);        // convert Orgs to lowercase letters
         }
         handler.insertOrg(kDataOrg, fileName);     // insert to AVLTree for Orgs
    }
    string splitWords = doc["text"].GetString();
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
        // if the currentWord is not a stop word
        if ((!lowerCaseLetters.empty()) && !isStopWord(lowerCaseLetters)) {
            Porter2Stemmer::stem(lowerCaseLetters);      // remove any stemming from the word
            handler.insertWord(lowerCaseLetters, fileName);
        }
        splitWords.erase(0, length + space_delimiter.length());
    }
}

void DocumentParser::parseFolder(const string &directory, IndexHandler &handler) {
    // https://www.delftstack.com/howto/cpp/how-to-get-list-of-files-in-a-directory-cpp/
    for (const auto & entry : std::filesystem::recursive_directory_iterator(directory)){
        if (entry.is_regular_file()) {
            if (entry.path().extension().string() == ".json") {
                string filename = entry.path().c_str();
                //cout << filename << std::endl;
                parse(filename, handler);
            }
        }
    }
}

bool DocumentParser::isStopWord(const string &currentWord) {
    map<string, int>::iterator it;    // https://www.cplusplus.com/reference/map/map/find/
    it = stopWords.find(currentWord);
    if (it == stopWords.end()) {    // if it's not in the map, add the word
        return false;
    }
    else {
        return true;
    }
}

void DocumentParser::readStopWords() {
    ifstream keywordFile("../stopWords.txt");     // read the file
    if (!keywordFile.is_open()) {
        cout << "Could not open file.";
    }
    string stopWord;     // stop word
    while (getline(keywordFile, stopWord)) {
        // needing to remove '\r' because I don't know what or why that keeps popping up
        // it's preventing the comparison between currentWord and stopWord
        stopWord.erase(remove(stopWord.begin(), stopWord.end(), '\r'), stopWord.end());
        stopWords.insert(pair<string, int> (stopWord, 1));
    }
    keywordFile.close();
}

void DocumentParser::printTree(IndexHandler &indexHandler) {
    indexHandler.traverse();
}

vector<string> DocumentParser::findDocuments(string &findKey, IndexHandler &indexHandler) {
    string lowerCaseLetters;
    for (auto& character : findKey) {       // convert strings to lower case
        character = tolower(character);
        if ((character >= 'a') && (character <= 'z')) {
            lowerCaseLetters = lowerCaseLetters + character;    // include only characters from a-z
        }
    }
    Porter2Stemmer::stem(lowerCaseLetters);
    return indexHandler.findWord(lowerCaseLetters);
}
// give this function a list of the user's keywords and the docs that they appear in
vector<pair<string, int>> DocumentParser::rankRelevancy(const vector<string> &userKeywords, vector<string> &docs) {
    readStopWords();    // read the stopWords list
    // first: remove duplicates from the docs vector
    sort( docs.begin(), docs.end() );
    docs.erase( unique( docs.begin(), docs.end() ), docs.end() );
    // second: reopen the result files
    rapidjson::Document doc;
    // pair of documents and how many times a userKeyword shows up in the given document
    vector<pair<string, int>> results;
    // iterate through the docs
    for (int i = 0; i < docs.size(); ++i) {
        ifstream streamy (docs[i]);
        // put the whole file's data into wholeFile
        string wholeFile;
        string temp;
        while(getline(streamy,temp)) {
            wholeFile += temp;
        }
        streamy.close ();
        // call parse on the string
        doc.Parse (wholeFile.c_str());          // covert the whole file to const char*
        string splitWords = doc["text"].GetString();    // look in the "text" section
        string space_delimiter = " ";           // space is the delimiter
        size_t length = 0;     // size_t assures the position will never be negative
        int counter{0}; // how many times a key word is found in the document
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
            // if the currentWord is not a stop word
            if ((!lowerCaseLetters.empty()) && !isStopWord(lowerCaseLetters)) {
                Porter2Stemmer::stem(lowerCaseLetters);      // remove any stemming from the word
                // check if the individual word is a keyword from user input
                for (int j = 0; j < userKeywords.size(); ++j) {
                    if (lowerCaseLetters == userKeywords[j]) {      // if it is a user keyword increase the counter
                        counter++;
                    }
                }
            }
            splitWords.erase(0, length + space_delimiter.length());
        }   // end while there are words left in the document

        // At this point, all words in a SINGLE document is read and counted
        // counter = the number of times a keyword was found in the document
        // docs[i] is the document name
        // now make the pair of a single result to add to the vector of the results
        pair<string, int> singleResult(docs[i],counter);
        results.push_back(singleResult);        // push the single results to the results vector
    }   // the end for every document
    return results;
}


