#include "InvertedIndex.h"

#include "../exceptions/Exceptions.h"

using namespace std;

InvertedIndex::InvertedIndex(deque<Document> documents)
        : documents(move(documents)) {}

double InvertedIndex::getDocumentWeightByID(int ID) {
    Document document{};

    if (documents.empty())
        throw EndOfIndexException();

    while ((document = documents.front()).getID() != ID) {
        if (documents.empty()) //end of the index; index is exhausted
            throw EndOfIndexException();
        if (document.getID() > ID) // IDs are sorted asc, i.e. if doc ID is higher, then the ID for is not in index
            throw IDNotFoundException();
        documents.pop_front();
    }

    documents.pop_front();
    return document.getWeight();
}

const Document &InvertedIndex::operator[](size_t index) {
    return documents[index];
}

int InvertedIndex::getNextID() const {
    return documents.front().getID();
}



