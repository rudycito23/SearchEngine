//
// Created by rrluc on 4/21/2022.
//

#include "QueryProcessor.h"

// how to process the user's query
void QueryProcessor::processQuery(const string &userQuery, IndexHandler &handler) {
    string currentWord;                 // Have a buffer string
    stringstream ss(userQuery);       // Insert the string into a stream
    vector<std::string> result; // Create vector to hold our words

    // NOT = -1
    // OR = 0
    // AND = 1
    int operand{0};

    // keyword = 0
    // ORG = -1
    // PERSON = 1
    int indicator{0};
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();
    while (ss >> currentWord) {
        std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
        start = std::chrono::high_resolution_clock::now();
        if (currentWord == "AND") {     // if the word = AND
            operand = 1;
        }
        else if (currentWord == "NOT") {    // if the word = NOT
            operand = -1;
        }
        else if (currentWord == "OR") {     // if the word = OR
            operand = 0;
        }
        else if (currentWord == "ORG") {       // if the word = ORG
            indicator = -1;
        }
        else if (currentWord == "PERSON") {     // if the word = PERSON
            indicator = 1;
        }
        else if (currentWord == "stop") {       // if the word = stop
            break;
        }
        else {
            for (int i = 0; i < currentWord.size(); ++i) {
                currentWord[i] = tolower(currentWord[i]);
            }
            Porter2Stemmer::stem(currentWord);      // remove any stemming from the word
            vector<string> tempResult;      // vector that contains the result
            if (indicator == 0) {      // if the user's query is a single keyword,
                // then call the handler to find the word and store it in tempResult vector
                tempResult = handler.findWord(currentWord);
            }
            else if (indicator == 1) {      // if it's a PERSON,
                // then call the handler to find the PERSON and store it in tempResult vector
                tempResult = handler.findPerson(currentWord);
            }
            else if (indicator == -1) {     // if it's an ORG,
                // then call the handler to find the ORG and store it in tempResult vector
                tempResult = handler.findOrg(currentWord);
            }
            if (operand == 1) {         // if query contains AND, continue for next check
                // for any AND or OR, push the currentWord into the userKeywords vector
                userKeywords.push_back(currentWord);
                if (result.empty()) {   // if the result is empty,
                    result = tempResult;    // store the tempResult in result
                }
                else {      // else, find the intersection of result and tempResult, then store it in result
                    result = intersection(result, tempResult);
                }
            }
            else if (operand == 0) {        // if the query contains OR,
                userKeywords.push_back(currentWord);
                // call the combineVectors function and store it in the result vector
                result = combineVectors(result, tempResult);
            }
            else if (operand == -1) {       // if the query contains NOT
                // call the deleteVector function
                deleteVector(result, tempResult);
            }
            indicator = 0;      // reset the indicator trigger
        }
    }
    end = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration<double>(end - start).count();
    cout << "(" << time << " second(s) to complete)" << endl << endl;
    rankAndReorder(result);      // returning the rankAndReorder()
}
// Step 1: find the current word
// Step 2: find the intersection between result and tempResult

// https://stackoverflow.com/questions/19483663/vector-intersection-in-c
// intersection algo from the <algorithm> library
vector<string> QueryProcessor::intersection(vector<string> &vector1, vector<string> &vector2) {
    vector<string> vector3;     // vector3 is the result of the intersection between vector1 & vector2
    // execute the intersection
    set_intersection(vector1.begin(), vector1.end(), vector2.begin(), vector2.end(),back_inserter(vector3));
    return vector3;     // return vector3 which is the result after the intersection
}

// https://stackoverflow.com/questions/3385229/c-erase-vector-element-by-value-rather-than-by-position
// delete by the key value instead
void QueryProcessor::deleteVector(vector<string> &vector1, vector<string> vector2) {
    for (int i = 0; i < vector2.size(); ++i) {      // iterate through the second vector
        // execute the deletion
        vector1.erase(remove(vector1.begin(), vector1.end(), vector2[i]), vector1.end());
    }
}

//  https://stackoverflow.com/questions/3177241/what-is-the-best-way-to-concatenate-two-vectors
// combine the vectors for *OR* query
vector<string> QueryProcessor::combineVectors(vector<string> vector1, vector<string> vector2) {
    vector<string> vector3;     // vector3 is the final result after combining vector1 and vector2
    vector3.reserve( vector1.size() + vector2.size() ); // preallocate memory
    vector3.insert( vector3.end(), vector1.begin(), vector1.end() );
    vector3.insert( vector3.end(), vector2.begin(), vector2.end() );

    return vector3;     // return vector3 after combining vector1 & vector2
}

// https://www.geeksforgeeks.org/sorting-vector-of-pairs-in-c-set-1-sort-by-first-and-second/
// sort vectors by the second element
bool sortBySecondElement(const pair<string,int> &pair1, const pair<string,int> &pair2)
{
    return (pair1.second > pair2.second);
}
// calls parser to reopen documents and count and rank relevancy of the documents
void QueryProcessor::rankAndReorder(vector<string> &results) {
    DocumentParser parser;
    // call the rankRelevancy function from DocumentParser
    // to display how many times the key appears in the document
    if (results.empty()) {
        cout << "No results found.  Try another search." << endl << endl;
        return;
    }
    vector<pair<string, int>> rankedDocs = parser.rankRelevancy(userKeywords, results);
    sort(rankedDocs.begin(), rankedDocs.end(), sortBySecondElement);

    int howManyToPrint = min(15,(int)rankedDocs.size());    // print a maximum of 15 results
    for (int i = 0; i < howManyToPrint; ++i) {
        // first = string and second = counter
        cout << "Article #" << i + 1 << endl;
        parser.showContent(rankedDocs[i].first);
        cout << endl << endl;
    }
    cout << "What article would you like to read?" << endl;
    string userChoice;
    getline(cin, userChoice);
    if ((stoi(userChoice) < 1) || (stoi(userChoice) > howManyToPrint)) {    // stoi = string to int conversion
        cout << "Invalid entry." << endl;
    }
    else {
        // call printArticle from DocumentParser
        parser.printArticle(rankedDocs[stoi(userChoice) - 1].first);
        cout << endl;
    }
}