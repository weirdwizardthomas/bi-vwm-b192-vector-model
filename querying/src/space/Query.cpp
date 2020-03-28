//
// Created by tomas on 3/23/20.
//

#include "Query.h"

using namespace std;

Query::Query(std::map<std::string, double> terms, const double threshold)
        : terms(std::move(terms)), threshold(threshold) {}
