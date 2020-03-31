#include "ArgumentParser.h"

using namespace std;
using namespace cxxopts;

ArgumentParser::ArgumentParser() : options("Information retrieval - querying", "Queries against a collection.") {
    options.add_options()
            ("c,collection", "Document collection SQLite3 database", cxxopts::value<string>())
            ("i,index", "Inverted index JSON file", cxxopts::value<string>())
            ("h,help", "Print usage");
}

int ArgumentParser::parse(int argc, char **argv) {
    ParseResult parseResult = options.parse(argc, argv);

    if (parseResult.count("help"))
        return HELP;

    if (!parseResult.count("index") || !parseResult.count("collection"))
        return PARSE_FAILURE;

    databasePath = parseResult["collection"].as<string>();
    indexPath = parseResult["index"].as<string>();

    return PARSE_SUCCESS;
}

std::string ArgumentParser::getDatabasePath() const {
    return databasePath;
}

std::string ArgumentParser::getIndexPath() const {
    return indexPath;
}

std::string ArgumentParser::getHelp() const {
    return options.help();
}
