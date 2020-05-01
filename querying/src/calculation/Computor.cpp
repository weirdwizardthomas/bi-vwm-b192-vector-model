#include <iostream>
#include <climits>
#include <utility>
#include <algorithm>
#include <cmath>

#include "Computor.h"
#include "../enum/EInvertedIndex.h"

using namespace std;

Computor::Computor(Space space, Query query)
        : space(std::move(space)),
          query(std::move(query)) {}

vector<pair<int, double>> Computor::compute(Database & database) {
    vector<pair<int, double>> results;
    map<int, double> vectorSizes = database.getVectorSizes();

    availableTerms = query.termsKeyset;

    double vectorQuerySize;
    for (const auto & entry : query.terms)
        vectorQuerySize += entry.second * entry.second;

    while (!availableTerms.empty()) {
        int ID = nextID(); //get lowest ID
        double result = 0, denominator = 0;

        for (const auto &term: availableTerms) /*Go through all the remaining terms*/ {

            double documentWeight = space.getInvertedIndexByKey(term).getDocumentWeightByID(ID);

            if (documentWeight == EInvertedIndex::IDNotFound) //inverted index does not contain given ID
                continue;

            if (documentWeight == EInvertedIndex::EndOfIndex) {
                availableTerms.erase(term); //remove term from further computation
                continue;
            }

            double queryWeight = query.terms.at(term);
            result += documentWeight * queryWeight;
        }

        denominator = sqrt(vectorSizes[ID] * vectorQuerySize);
        // Input should not be zero vector but if it is, do not divide and "just" return wrong result..
        if (denominator != 0)
            result = result / denominator;

        if (result > query.threshold) //filter out irrelevant documents
            results.emplace_back(make_pair(ID, result));
    }

    std::sort(results.begin(), results.end(), [] (const pair<int, double> & a, const pair<int, double> & b)
                                         { return a.second > b.second; });

    return results;
}

int Computor::nextID() {
    int lowestID = INT_MAX;

    for (const auto &term: availableTerms)
        lowestID = min(space[term].getNextID(), lowestID);

    return lowestID;
}
