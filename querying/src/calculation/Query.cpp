#include "Query.h"

using namespace std;

Query::Query(std::map<std::string, double> t, double threshold)
        : termsKeyset(createKeyset(t)),
          terms(std::move(t)),
          threshold(threshold) {}

set<string> Query::createKeyset(const map<std::string, double> &t) {
    set<string> dummy;
    for (const auto &term: t)
        dummy.emplace(term.first);
    return dummy;
}
