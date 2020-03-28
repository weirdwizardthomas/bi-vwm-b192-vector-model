//
// Created by TomTom on 28.03.2020.
//

#ifndef QUERYING_QUERYJSONPARSER_H
#define QUERYING_QUERYJSONPARSER_H

#include <iostream>
#include <fstream>

#include "../../lib/json.hpp"

using json = nlohmann::json;

class QueryJSONParser {
private:
    //Attributes-------------
    std::ifstream fileStream; /**<File stream of the read JSON file*/
    const std::string filePath;/**<Path to the JSON file*/

    //Methods----------------
    /**
     * Loads a JSON from a file @ref filePath
     * @throws invalid_argument if stream opening is not successful (i.e. file cannot be loaded)
     * @return JSON structure
     */
    nlohmann::json loadJsonFromFile();

public:
    //Methods----------------
    /**
     * Constructor
     * @param filePath Path of the JSON file to be processed
     */
    explicit QueryJSONParser(std::string filePath);

    /**
     * Loads and parses a JSON file specified by @ref filePath
     * @return Parsed data of the JSON file,
     * where key = term name, value = inverted index list of the term
     */
    std::map<std::string, double> parse();
};


#endif //QUERYING_QUERYJSONPARSER_H
