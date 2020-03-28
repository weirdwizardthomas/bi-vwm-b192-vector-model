//
// Created by tomas on 3/24/20.
//

#include "Document.h"

Document::Document(const int id, const double weight) : ID(id), weight(weight) {}

int Document::getID() const {
    return ID;
}

double Document::getWeight() const {
    return weight;
}

