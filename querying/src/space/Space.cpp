//
// Created by tomas on 3/23/20.
//

#include "Space.h"

using namespace std;

Space::Space(map<string, InvertedIndex> terms) : terms(move(terms)) {}


const InvertedIndex &Space::operator[](const string &key) const {
    return terms.at(key);
}

InvertedIndex &Space::getInvertedIndexByKey(const string &key) {
    return terms.at(key);
}

void Space::forward(int ID, const std::map<std::string, double> q) {
    for (const auto &term: q)
        terms.at(term.first).forward(ID);
}



