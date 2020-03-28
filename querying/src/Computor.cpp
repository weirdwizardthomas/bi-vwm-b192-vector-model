#include <iostream>
#include <climits>
#include <utility>
#include "Computor.h"
#include "exceptions/Exceptions.h"

using namespace std;

Computor::Computor(Space space, Query query) : space(std::move(space)), query(std::move(query)) {}


map<int, double> Computor::compute() {
    map<int, double> results;

    availableTerms = query.termsKeyset;

    while (!availableTerms.empty()) {
        int ID = nextID(); //get lowest ID
        double result = 0;

        for (const auto &term: availableTerms) /*Go through all the remaining terms*/ {
            try {
                double queryWeight = query.terms.at(term);
                double documentWeight = space.getInvertedIndexByKey(term).getDocumentWeightByID(ID);
                result += documentWeight * queryWeight;
            }
            catch (const IDNotFoundException &e) {//inverted index does not contain given ID
            }

            catch (const EndOfIndexException &e) {
                availableTerms.erase(term); //exhaust term
            }
        }
        results[ID] = result;
    }

    return results;
}

int Computor::nextID() {
    int lowestID = INT_MAX;

    for (const auto &queryRecord: query.terms)
        lowestID = min(space[queryRecord.first].getLowestID(), lowestID);

    return lowestID;
}


