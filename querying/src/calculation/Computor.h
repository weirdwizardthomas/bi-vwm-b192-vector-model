//
// Created by tomas on 3/23/20.
//

#ifndef QUERYING_COMPUTOR_H
#define QUERYING_COMPUTOR_H

#include <map>
#include "Space.h"
#include "Query.h"

/**
 * @brief A class that encompasses the calculation of a document's relevancy to the query
 *
 * @author koristo1@fit.cvut.cz
 */
class Computor {
private:
    //Attributes--------------
    Space space; /**< Term space */
    std::set<std::string> availableTerms; /**< Non exhausted terms of the query */

    //Methods-----------------
    /**
     * Finds the next ID for computation
     * @return next eligible ID in @ref Space::terms
     */
    int nextID();

public:
    //Attributes--------------
    const Query query;/**< Query against the space */

    //Methods-----------------
    Computor(Space space, Query query);

    /**
     * @brief Computes relevancies of documents to the query
     *
     * Filters relevancies that are below @ref Query::threshold
     * @return Map of document IDs and their relevancies to the query
     */
    std::map<int, double> compute();
};


#endif //QUERYING_COMPUTOR_H
