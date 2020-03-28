#ifndef QUERYING_SPACE_H
#define QUERYING_SPACE_H


#include <string>
#include <set>
#include <map>

#include "InvertedIndex.h"
#include "Query.h"

/**
 * @brief A class representing the vector space of the collection
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
     * @param terms Terms defining the space; and their inverted indices
     */
    explicit Space(std::map<std::string, InvertedIndex> terms);

    /**
     * @brief Gets an element from @ref Space::terms with key @ref key
     * @param key Key of the element to find
     * @return Value of @ref Space::terms at @ref key
     */
    InvertedIndex &getInvertedIndexByKey(const std::string &key);

    /**
     * @brief Gets an element from @ref Space::terms with key @ref key
     * @param key Key of the element to find
     * @return Value of @ref Space::terms at @ref key
     */
    const InvertedIndex &operator[](const std::string &key) const;
};


#endif //QUERYING_SPACE_H
