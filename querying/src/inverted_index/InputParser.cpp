//
// Created by tomas on 3/23/20.
//

#include "InputParser.h"

#include <utility>
#include "../../lib/json.hpp"

using namespace std;

using json = nlohmann::json;

InputParser::InputParser(string filePath) : filePath(move(filePath)) {}

map<string, InvertedIndex> InputParser::getInvertedIndices() {
    json root = loadJsonFromFile();
    map<string, InvertedIndex> invertedIndices;
    for (const auto &[term, documentIDs]: root.items()) {
        vector<DocumentWeight> weights;

        for (const auto &[documentID, weight] :  documentIDs.items())
            weights.emplace_back(stoi(documentID), weight);

        sort(weights.begin(), weights.end(),
             [](const auto &a, const auto &b) { return a.getID() < b.getID(); });

        invertedIndices.insert({term, InvertedIndex(term, weights)});
    }

    return invertedIndices;
}

json InputParser::loadJsonFromFile() {
    fileStream = ifstream(filePath);

    if (fileStream.fail())
        throw invalid_argument("Invalid filepath to inverted list");

    json root;
    fileStream >> root;

    return root;
}

