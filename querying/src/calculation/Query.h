#ifndef QUERYING_QUERY_H
#define QUERYING_QUERY_H


#include <map>
#include <set>
#include <vector>
#include <string>
#include "Space.h"

/**
 * @brief A data class representing user query against the collection
 *
 * @author koristo1@fit.cvut.cz
 */
class Query {
public:
    //Attributes-------------
    const std::set<std::string> termsKeyset; /**<Keyset of terms */
    const std::map<std::string, double> terms; /**<Terms and their weights in the query */
    const double threshold; /**<Acceptable result threshold */

    //Methods----------------
    /**
     * Constructor
     * @param terms Terms and their weights in the query
     * @param threshold Acceptable result threshold
     */
    explicit Query(std::map<std::string, double> t, double threshold);

    /**
     * Extracts the keyset from the @ref t map
     * @param t A map from which the keyset is to extract
     * @return keys of @ref t
     */
    static std::set<std::string> createKeyset(const std::map<std::string, double> &t);
};


#endif //QUERYING_QUERY_H
