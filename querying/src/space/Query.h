#ifndef QUERYING_QUERY_H
#define QUERYING_QUERY_H


#include <map>
#include <vector>
#include <string>
#include "Space.h"

/**
 * @brief A class representing user query against the collection
 */
class Query {
public:
    //Attributes-------------
    const std::map<std::string, double> terms; /**<Terms and their weights in the query */
    const double threshold; /**<Acceptable result threshold */

    //Methods----------------
    /**
     * Constructor
     * @param terms Terms and their weights in the query
     * @param threshold Acceptable result threshold
     */
    explicit Query(std::map<std::string, double> terms, const double threshold);
};


#endif //QUERYING_QUERY_H
