#include <iostream>
#include <climits>
#include <utility>
#include <algorithm>
#include <cmath>

#include "Computor.h"
#include "../exceptions/Exceptions.h"

using namespace std;

Computor::Computor(Space space, Query query)
        : space(std::move(space)),
          query(std::move(query)) {}

vector<pair<int, double>> Computor::compute(Database & database, int document_id) {
    vector<pair<int, double>> results;
    map<string, double> currentDocument = space.getTermsAndWeightsByID(database, document_id);

    availableTerms = query.termsKeyset;

    while (!availableTerms.empty()) {
        int ID = nextID(); //get lowest ID
        double result = 0, denominator = 0, tmp = 0;

        for (const auto &term: availableTerms) /*Go through all the remaining terms*/ {
            try {
                double documentWeight = space.getInvertedIndexByKey(term).getDocumentWeightByID(ID);
                double queryWeight = query.terms.at(term);
                result += documentWeight * queryWeight;
            }
            catch (const IDNotFoundException &e) {//inverted index does not contain given ID
            }

            catch (const EndOfIndexException &e) {
                availableTerms.erase(term); //exhaust term
            }
        }

        for (const auto & entry : query.terms)
            denominator += entry.second * entry.second;
        
        for (const auto & entry : currentDocument)
            tmp += entry.second * entry.second;

        denominator = sqrt(denominator * tmp);
        // Input should not be zero vector but if it is, do not divide and "just" return wrong result..
        if (denominator != 0)
            result = result / denominator;

        if (result > query.threshold) //filter out irrelevant documents
            results.emplace_back(make_pair(ID, result));
    }

    sort(results.begin(), results.end(), [] (const pair<int, double> & a, const pair<int, double> & b)
                                         { return a.second > b.second; });

    return results;
}

int Computor::nextID() {
    int lowestID = INT_MAX;

    for (const auto &term: availableTerms)
        lowestID = min(space[term].getNextID(), lowestID);

    return lowestID;
}
