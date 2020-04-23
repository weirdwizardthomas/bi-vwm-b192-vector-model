#include "InvertedIndexJSONParser.h"

#include <utility>
#include <deque>
#include "../../lib/json.hpp"

using namespace std;

using json = nlohmann::json;

InvertedIndexJSONParser::InvertedIndexJSONParser(string filePath)
        : filePath(move(filePath)) {}

map<string, InvertedIndex> InvertedIndexJSONParser::parse() {
    json root = loadJsonFromFile();
    map<string, InvertedIndex> invertedIndices;

    for (const auto &[term, documentIDs]: root.items()) {
        deque<WeightedDocument> weights;

        for (const auto &[documentID, weight] :  documentIDs.items())
            weights.emplace_back(stoi(documentID), weight);

        sort(weights.begin(), weights.end(),
             [](const auto &a, const auto &b) { return a.getID() < b.getID(); }); //sort according to document ID

        invertedIndices.emplace(term, InvertedIndex(weights));
    }

    return invertedIndices;
}

json InvertedIndexJSONParser::loadJsonFromFile() {
    fileStream = ifstream(filePath);

    if (fileStream.fail())
        throw invalid_argument("Invalid filepath to inverted list");

    json root;
    fileStream >> root;

    return root;
}

