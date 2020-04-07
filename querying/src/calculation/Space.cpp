//
// Created by tomas on 3/23/20.
//

#include "Space.h"

using namespace std;

Space::Space(map<string, InvertedIndex> terms)
        : terms(move(terms)) {}


const InvertedIndex &Space::operator[](const string &key) const {
    return terms.at(key);
}

InvertedIndex &Space::getInvertedIndexByKey(const string &key) {
    return terms.at(key);
}

const map<string, double> Space::getTermsAndWeightsByID(Database & database, int document_id) {
    map<string, double> terms;
    vector<string> dummy = database.getTermsByDocumentID(document_id);

    for (string term : dummy) {
        InvertedIndex tmp = getInvertedIndexByKey(term);
        terms[term] = tmp.getDocumentWeightByID(document_id);
    }

    return terms;
}
