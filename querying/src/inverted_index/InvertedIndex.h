#ifndef QUERYING_INVERTEDINDEX_H
#define QUERYING_INVERTEDINDEX_H


#include <string>
#include <deque>
#include "../Document.h"

/**
 * @brief Data container of term and its inverted index list
 *
 * @author koristo1@fit.cvut.cz
 */
class InvertedIndex {
private:
    //Attributes-------------
    std::deque<Document> documents; /**<Inverted index list of documents & their weights in which the term appears */

public:

    //Methods-----------------
    /**
     * Constructor
     * @param documentWeights Inverted index list of documents in which the term appears, and their weights
     */
    explicit InvertedIndex(std::deque<Document> documentWeights);

    /**
     * @brief Finds the @ref Document object with a given @ref Document::ID in @ref documents
     *
     * Given an ID, looks through the container starting at @ref position.
     * Assumes that the items are sorted by @ref Document::ID, ascending.
     *
     * @param ID @ref Document::ID to be found.
     * @throws IDNotFoundException if no Document is found or it had been processed already
     * @return Document with @ref Document::ID ==  ID
     */
    double getDocumentWeightByID(int ID);

    int getLowestID() const;

    const Document &operator[](size_t i);
};


#endif //QUERYING_INVERTEDINDEX_H
