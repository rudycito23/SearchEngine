//
// Created by rrluc on 4/21/2022.
//

#ifndef INC_22S_FINAL_PROJ_QUERYPROCESSOR_H
#define INC_22S_FINAL_PROJ_QUERYPROCESSOR_H

#include "IndexHandler.h"
#include <sstream>
#include <algorithm>
#include "DocumentParser.h"

using std::stringstream;
using std::vector;
using std::sort;
using std:: min;

class QueryProcessor {
private:
    vector<string> userKeywords;

public:
    void processQuery(const string&, IndexHandler&);
    void rankAndReorder(vector<string>&);
    vector<string> intersection(vector<string> &, vector<string> &);
    void deleteVector(vector<string> &, vector<string>);
    vector<string> combineVectors(vector<string>, vector<string>);


    // Implement functions to handle simple prefix Boolean queries by the user

    // A boolean expression will be prefixed with a Boolean operator of either *AND* or *OR*, if
    // there is more than one word of interest

    //  No search will contain both *AND* and *OR*

    // Single word searches (except for *NOT*, *ORG*, *PERSON*), do need a Boolean operator

    // Words that come before *NOT* return a result, but after *NOT* should be omitted.

    // A search can contain zero or more of the following:  ORG(organization name) - search an index
    // where you maintain organizations and their metadata,
    // Example: *basically an AVLTree<key organization, value fileContainsOrgName> orgTree*

    // A search can contain zero or more of the following:  PERSON(person name) - search an index
    // where you maintain organizations and their metadata,
    // Example: *basically an AVLTree<key personName, value fileContainsPersonName> orgTree*

    // order of *ORG* and *PERSON* doesn't matter (find away to accept queries in either order)

    // operators will be entered in ALL CAPS (convert to lower-case in my code)

    // *ORG* and *PERSON* will not be a search term

    // Ranking the Result: create a relevancy ranking to return the best results.
    // Research *inverse document frequency statistic* - maybe create a point system that will
    // score documents by the number of times the word appears in the document.  Return the highest scores


};


#endif //INC_22S_FINAL_PROJ_QUERYPROCESSOR_H
