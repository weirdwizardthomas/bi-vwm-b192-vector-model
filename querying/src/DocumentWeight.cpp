//
// Created by tomas on 3/24/20.
//

#include "DocumentWeight.h"

DocumentWeight::DocumentWeight(const int id, const double weight) : ID(id), weight(weight) {}

int DocumentWeight::getID() const {
    return ID;
}

double DocumentWeight::getWeight() const {
    return weight;
}

