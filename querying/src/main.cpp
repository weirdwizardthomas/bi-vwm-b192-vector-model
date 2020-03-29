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
            ("c,collection", "Document collection", cxxopts::value<string>())
            ("h,help", "Print usage");

    auto result = options.parse(argc, argv);

    if (result.count("help")) {
        cout << options.help() << std::endl;
        return EXIT_SUCCESS;
    }

    if (!result.count("collection"))
        return EXIT_FAILURE;

    auto collectionPath = result["collection"].as<string>();
    Space space(InvertedIndexJSONParser(collectionPath).parse());

    string queryPath;
    bool exit = false;
    double threshold;

    while (true) {
        cin >> exit;
        if (exit)
            break;

        cin >> queryPath >> threshold;
        Query query(QueryJSONParser(queryPath).parse(), threshold);
        auto res = Computor(space, query).compute();
        for (const auto &[id, value]: res)
            cout << id << ":" << value << endl;
    }

    return EXIT_SUCCESS;
}
