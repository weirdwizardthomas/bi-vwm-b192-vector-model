#include "InvertedIndex.h"

#include "../exceptions/Exceptions.h"

using namespace std;

InvertedIndex::InvertedIndex(string term, vector<DocumentWeight> documentWeights)
        : position(0),
          term(move(term)),
          documentWeights(move(documentWeights)) {}

double InvertedIndex::getDocumentWeightByID(int ID) {

    if (position + 1 == documentWeights.size())
        throw EndOfIndexException();

    for (auto it = documentWeights.begin() + position; it != documentWeights.end(); it++) {
        int documentID = (*it).getID();

        if (documentID < ID)
            throw IDNotFoundException();

        if (documentID == ID) //match!
        {
            position = it - documentWeights.begin() + 1; //update position
            return (*it).getWeight();
        }
    }

    /*

    for (size_t i = position; position < documentWeights.size(); ++i) {
        int documentID = documentWeights[i].getWeight();

        if (documentID < ID)
            throw IDNotFoundException();
        if (documentID == ID) {
            position = i + 1;
            return documentWeights[i];
        }
    }
*/

    throw IDNotFoundException();
}

const DocumentWeight &InvertedIndex::operator[](size_t i) {
    return documentWeights[i];
}

int InvertedIndex::getLowestID() const {
    return documentWeights[position].getID();
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

