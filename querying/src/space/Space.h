#ifndef QUERYING_SPACE_H
#define QUERYING_SPACE_H


#include <string>
#include <set>
#include <map>

#include "../inverted_index/InvertedIndex.h"
#include "Query.h"

/**
 * @brief Class representing the vector space of the collection
 *
 * @author koristo1@fit.cvut.cz
 */
class Space {
private:
    //Attributes-------------
    std::map<std::string, InvertedIndex> terms; /**<Terms and their inverted indices in the collection*/

public:

    //Methods----------------
    /**
     * Constructor
     * @param terms Terms and their inverted indices in the collection
     */
    explicit Space(std::map<std::string, InvertedIndex> terms);

    InvertedIndex &getInvertedIndexByKey(const std::string &key);

    const InvertedIndex &operator[](const std::string &key) const;

    void forward(int ID, const std::map<std::string, double> &q);
};


#endif //QUERYING_SPACE_H
