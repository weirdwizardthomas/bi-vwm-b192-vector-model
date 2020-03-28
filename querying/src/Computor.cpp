#include <iostream>
#include <climits>
#include "Computor.h"
#include "exceptions/Exceptions.h"

using namespace std;

Computor::Computor(Space space, const Query &query) : space(space), query(query) {}


map<int, double> Computor::compute() {
    exhaustedIndices = {};
    auto totalIndices = query.terms.size();

    int lowestDocumentID = nextID();
    space.forward(lowestDocumentID, query.terms);
    map<int, double> results;

    while (exhaustedIndices.size() != totalIndices) {
        results.emplace(lowestDocumentID, computeForDocument(lowestDocumentID));
        lowestDocumentID = nextID();
        space.forward(lowestDocumentID, query.terms);
    }

    return results;
}


double Computor::computeForDocument(int ID) {
    double result = 0;

    for (const auto &[term, weight]: query.terms) {
        try {
            auto d = space.getInvertedIndexByKey(term).getDocumentWeightByID(ID);
            result += weight * d;
        }

        catch (EndOfIndexException &e) {
            exhaustedIndices.emplace(term); //add another exhausted inverted index
        }
        catch (IDNotFoundException &e) {
            continue;
        }
    }

    return result;
}


int Computor::nextID() const {
    int nextID = INT_MAX;

    for (const auto &term: query.terms)
        nextID = min(space[term.first].getLowestID(), nextID);

    return nextID;
}

