#include "WeightedDocument.h"

WeightedDocument::WeightedDocument(int id, double weight)
        : ID(id), weight(weight) {}

int WeightedDocument::getID() const {
    return ID;
}

double WeightedDocument::getWeight() const {
    return weight;
}

