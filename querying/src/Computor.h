//
// Created by tomas on 3/23/20.
//

#ifndef QUERYING_COMPUTOR_H
#define QUERYING_COMPUTOR_H

#include <map>
#include "space/Space.h"
#include "space/Query.h"

class Computor {
private:
    //Attributes--------------
    Space space;
    const Query query;
    std::set<std::string> availableTerms;

    //Methods-----------------
    int nextID();

    double computeForDocument(int ID);

public:
    Computor(Space space, Query query);

    std::map<int, double> compute();
};


#endif //QUERYING_COMPUTOR_H
