//
// Created by tomas on 3/24/20.
//

#ifndef QUERYING_WEIGHTEDDOCUMENT_H
#define QUERYING_WEIGHTEDDOCUMENT_H

/**
 * @brief A data class of document's ID and it's weight for a given term
 *
 * @author koristo1@fit.cvut.cz
 */
class WeightedDocument {
private:
    //Attributes-------------
    int ID; /**< Document's database ID */
    double weight; /**< Weight of the document for a given term */

public:
    //Methods---------------
    WeightedDocument(int id, double weight);

    WeightedDocument() = default;

    int getID() const;

    double getWeight() const;
};


#endif //QUERYING_WEIGHTEDDOCUMENT_H
