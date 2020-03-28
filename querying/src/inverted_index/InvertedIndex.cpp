#include "InvertedIndex.h"

#include "../exceptions/Exceptions.h"

using namespace std;

InvertedIndex::InvertedIndex(deque<DocumentWeight> documentWeights)
        : documentWeights(move(documentWeights)) {}


double InvertedIndex::getDocumentWeightByID(int ID) {

    if (position + 1 == documentWeights.size())
        throw EndOfIndexException();


    while (documentWeights.front().getID() != ID) {
        documentWeights.pop_front();
    }
    return documentWeights.front().getID();

    for (auto it = documentWeights.begin() + position; it != documentWeights.end(); it++) {
        int documentID = (*it).getID();

        if (documentID < ID)
            throw IDNotFoundException();

        if (documentID == ID) //match!
            return (*it).getWeight();
    }

    throw IDNotFoundException();
}

const DocumentWeight &InvertedIndex::operator[](size_t i) {
    return documentWeights[i];
}

int InvertedIndex::getLowestID() const {
    return documentWeights.front().getID();
}

void InvertedIndex::forward(int ID) {
    auto it = documentWeights.begin() + position;

    while (it != documentWeights.end() && (*it).getID() != ID) {
        if (ID < (*it).getID())
            return;
        position++;
        it++;
    }
}

