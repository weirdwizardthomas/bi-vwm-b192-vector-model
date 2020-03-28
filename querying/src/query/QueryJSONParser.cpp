//
// Created by TomTom on 28.03.2020.
//

#include "QueryJSONParser.h"

using namespace std;

QueryJSONParser::QueryJSONParser(string filePath) :
        filePath(move(filePath)) {}

map<string, double> QueryJSONParser::parse() {
    json root = loadJsonFromFile();
    map<string, double> terms;

    for (const auto &[term, value]: root.items())
        terms.emplace(term, value);

    return terms;
}


nlohmann::json QueryJSONParser::loadJsonFromFile() {
    fileStream = ifstream(filePath);

    if (fileStream.fail())
        throw invalid_argument("Invalid filepath to inverted list");

    json root;
    fileStream >> root;

    return root;
}
    
