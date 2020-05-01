#include "InvertedIndex.h"

#include "../enum/EInvertedIndex.h"

using namespace std;

InvertedIndex::InvertedIndex(deque<WeightedDocument> documents)
        : documents(move(documents)) {}

double InvertedIndex::getDocumentWeightByID(int ID) {
    WeightedDocument document{};

    if (documents.empty())
        return EInvertedIndex::EndOfIndex;

    while ((document = documents.front()).getID() != ID) {
        if (documents.empty()) //end of the index; index is exhausted
            return EInvertedIndex::EndOfIndex;
        if (document.getID() > ID) // IDs are sorted asc, i.e. if doc ID is higher, then the ID for is not in index
            return EInvertedIndex::IDNotFound;
        documents.pop_front();
    }

    documents.pop_front();
    return document.getWeight();
}

const WeightedDocument &InvertedIndex::operator[](size_t index) {
    return documents[index];
}

int InvertedIndex::getNextID() const {
    return documents.front().getID();
}
