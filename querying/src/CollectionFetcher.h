//
// Created by tomas on 3/31/20.
//

#ifndef QUERYING_COLLECTIONFETCHER_H
#define QUERYING_COLLECTIONFETCHER_H

#include <vector>
#include <string>

class CollectionFetcher {
public:
    static std::vector<std::string> fetchCollection(const std::string &databasePath);
};


#endif //QUERYING_COLLECTIONFETCHER_H
