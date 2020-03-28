#ifndef QUERYING_INPUTPARSER_H
#define QUERYING_INPUTPARSER_H


#include <fstream>
#include <map>
#include "../../lib/json.hpp"

#include "InvertedIndex.h"

/**
 * @brief Class that handles loading a JSON file of inverted indices and parses it
 *
 * @author koristo1@fit.cvut.cz
 *
 */
class InputParser {
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
    explicit InputParser(std::string filePath);

    /**
     * Loads and parses a JSON file specified by @ref filePath
     * @return Parsed data of the JSON file,
     * where key = term name, value = inverted index list of the term
     */
    std::map<std::string, InvertedIndex> getInvertedIndices();
};


#endif //QUERYING_INPUTPARSER_H
