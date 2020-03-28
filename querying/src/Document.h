//
// Created by tomas on 3/24/20.
//

#ifndef QUERYING_DOCUMENT_H
#define QUERYING_DOCUMENT_H


class Document {
private:
    int ID;
    double weight;

public:
    Document(int id, double weight);

    Document() = default;

    int getID() const;

    double getWeight() const;

};


#endif //QUERYING_DOCUMENT_H
