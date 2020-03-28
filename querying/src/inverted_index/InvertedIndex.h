#ifndef QUERYING_INVERTEDINDEX_H
#define QUERYING_INVERTEDINDEX_H


#include <string>
#include <deque>
#include "../DocumentWeight.h"

/**
 * @brief Data container of term and its inverted index list
 *
 * @author koristo1@fit.cvut.cz
 */
class InvertedIndex {
private:
    //Attributes-------------
    std::deque<DocumentWeight> documentWeights; /**<Inverted index list of documents & their weights in which the term appears */

public:

    //Methods-----------------
    /**
     * Constructor
     * @param documentWeights Inverted index list of documents in which the term appears, and their weights
     */
    InvertedIndex(std::deque<DocumentWeight> documentWeights);

    /**
     * @brief Finds the @ref DocumentWeight object with a given @ref DocumentWeight::ID in @ref documentWeights
     *
     * Given an ID, looks through the container starting at @ref position.
     * Assumes that the items are sorted by @ref DocumentWeight::ID, ascending.
     *
     * @param ID @ref DocumentWeight::ID to be found.
     * @throws IDNotFoundException if no Document is found or it had been processed already
     * @return DocumentWeight with @ref DocumentWeight::ID ==  ID
     */
    double getDocumentWeightByID(int ID);

    int getLowestID() const;

    const DocumentWeight &operator[](size_t i);
};


#endif //QUERYING_INVERTEDINDEX_H
