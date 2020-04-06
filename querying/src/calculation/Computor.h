//
// Created by tomas on 3/23/20.
//

#ifndef QUERYING_COMPUTOR_H
#define QUERYING_COMPUTOR_H

#include <vector>

#include "Space.h"
#include "Query.h"
#include "./../database/Terms.h"

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
     * @return Vector of pairs with document IDs and their similarity to the query, sorted by similarity desc
     */
    std::vector<std::pair<int, double>> compute(Terms & collection, int document_id);
};


#endif //QUERYING_COMPUTOR_H
