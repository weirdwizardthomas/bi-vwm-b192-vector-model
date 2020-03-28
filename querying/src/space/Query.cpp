//
// Created by tomas on 3/23/20.
//

#include "Query.h"

using namespace std;

Query::Query(std::map<std::string, double> terms, double threshold)
        : terms(std::move(terms)),
          termsKeyset(getKeyset(terms)),
          threshold(threshold) {}

set<string> Query::getKeyset(const map<std::string, double> &terms) {
    set<string> dummy;
    for (const auto &term: terms)
        dummy.emplace(term.first);
    return dummy;
}
