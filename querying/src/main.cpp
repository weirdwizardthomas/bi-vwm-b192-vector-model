
#include <iostream>
#include <map>

#include <QApplication>

#include "../lib/cxxopts.hpp"
#include "calculation/Query.h"
#include "calculation/Space.h"
#include "calculation/Computor.h"
#include "util/QueryJSONParser.h"
#include "util/InvertedIndexJSONParser.h"
#include "src/ui/forms/mainform.h"
#include "CollectionFetcher.h"

static const int HELP_INDICATOR = 1;
static const int SUCCESS_INDICATOR = 0;
static const int FAILURE_INDICATOR = 2;
using namespace std;
using namespace cxxopts;

pair<int, string> parseArguments(int argc, char **argv) {
    Options options("Information retrieval - querying", "Queries against a collection.");
    options.add_options()
            ("c,collection", "Document collection", cxxopts::value<string>())
            ("h,help", "Print usage");

    auto result = options.parse(argc, argv);

    if (result.count("help"))
        return {HELP_INDICATOR, options.help()};

    if (!result.count("collection"))
        return {FAILURE_INDICATOR, ""};

    return {SUCCESS_INDICATOR, result["collection"].as<string>()};
}

int main(int argc, char *argv[]) {

    auto arg = parseArguments(argc, argv);
    switch (arg.first) {
        case SUCCESS_INDICATOR: {
            break;
        }
        case HELP_INDICATOR : {
            cout << arg.second << endl;
            return EXIT_SUCCESS;

        }
        case FAILURE_INDICATOR: {
            //todo error message
            return EXIT_FAILURE;
        }
    }

    Space space(InvertedIndexJSONParser(arg.second).parse());

    auto availableDocuments = CollectionFetcher::fetchCollection("../../data/persistence/docs_and_terms.db");

    QApplication application(argc, argv);

    MainForm mainForm;
    mainForm
            .setAvailableDocuments(availableDocuments)
            .setResults({"a", "b", "c"})
            .setOpenedDocument(availableDocuments[0]);
    mainForm.show();


    return QApplication::exec();
}

/*
int main(int argc, char **argv) {

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
*/
