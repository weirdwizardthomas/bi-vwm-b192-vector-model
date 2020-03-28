//
// Created by tomas on 3/24/20.
//

#ifndef QUERYING_DOCUMENTWEIGHT_H
#define QUERYING_DOCUMENTWEIGHT_H


class DocumentWeight {
private:
    int ID;
    double weight;

public:
    DocumentWeight(int id, double weight);

    int getID() const;

    double getWeight() const;
};


#endif //QUERYING_DOCUMENTWEIGHT_H
