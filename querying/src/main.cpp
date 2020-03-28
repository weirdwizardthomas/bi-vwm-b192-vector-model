#include <iostream>

#include "calculation/Query.h"
#include "calculation/Space.h"
#include "calculation/Computor.h"
#include "../lib/cxxopts.hpp"
#include "util/QueryJSONParser.h"
#include "util/InvertedIndexJSONParser.h"

using namespace std;
using namespace cxxopts;

int main(int argc, char **argv) {
    Options options("Information retrieval - querying", "Queries against a collection.");
    options.add_options()
            ("q,query", "Search query", cxxopts::value<string>())
            ("c,collection", "Document collection", cxxopts::value<string>())
            ("t,threshold", "Document filter threshold", cxxopts::value<double>()->default_value("0.5"))
            ("h,help", "Print usage");


    auto result = options.parse(argc, argv);

    if (result.count("help")) {
        cout << options.help() << std::endl;
        return EXIT_SUCCESS;
    }

    if (!result.count("query") || !result.count("collection") || !result.count("threshold"))
        return EXIT_FAILURE;

    auto threshold = result["threshold"].as<double>();
    auto queryPath = result["query"].as<string>();
    auto collectionPath = result["collection"].as<string>();

    Space space(InvertedIndexJSONParser(collectionPath).parse());
    Query query(QueryJSONParser(queryPath).parse(), threshold);

    auto res = Computor(space, query).compute();
    for (const auto &[id, value]: res)
        cout << id << ":" << value << endl;
    return EXIT_SUCCESS;
}
