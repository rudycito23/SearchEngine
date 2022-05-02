//
// Created by rrluc on 4/13/2022.
//

#include "DocumentParser.h"

DocumentParser::DocumentParser() {
    readStopWords();
}

void DocumentParser::parse(const string &fileName, IndexHandler &handler) {            // parser function
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
    // if (doc.IsObject ()) cout << "ITS AN OBJECT" << endl << endl;
    // loop over all the values of array
     for (auto &v : doc["entities"]["persons"].GetArray ()) {
         string kDataPerson = v.GetObject().begin()->value.GetString();     // convert Persons to strings
         for (int i = 0; i < kDataPerson.size(); ++i) {
             kDataPerson[i] = tolower(kDataPerson[i]);      // convert Person to lowercase letters
         }
         handler.insertPerson(kDataPerson, fileName);       // inserting to AVLTree for Persons
     }
     for (auto &v : doc["entities"]["organizations"].GetArray ()) {
         string kDataOrg = v.GetObject().begin()->value.GetString();        // convert Orgs to strings
         for (int i = 0; i < kDataOrg.size(); ++i) {
             kDataOrg[i] = tolower(kDataOrg[i]);        // convert Orgs to lowercase letters
         }
         handler.insertOrg(kDataOrg, fileName);     // insert to AVLTree for Orgs
    }
    string splitWords = doc["text"].GetString();
    //cout << "Words: " << splitWords << endl;         // prints the words from the actual blog

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

    //DIR *dir; struct dirent *diread;
    /*
    if ((dir = opendir(argv[1])) != nullptr) {
        while ((diread = readdir(dir)) != nullptr) {
            string file = string(diread->d_name);
            if ((file != "..") && file != ".") {
                string fileName = string(argv[1]) + "/" + string(diread->d_name);
                docParser.parse(fileName);
            }
        }
        closedir (dir);
    } else {
        perror ("opendir");
        return EXIT_FAILURE;
    }
    docParser.printTree();
    return EXIT_SUCCESS;
*/
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