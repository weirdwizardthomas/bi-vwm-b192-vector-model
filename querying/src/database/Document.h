#pragma once

#include <string>

/**
 * @brief A data class that represents the Document table
 *
 * @author koristo1@fit.cvut.cz
 */
class Document {
public:
    const int id; /**<ID column value */
    const std::string name; /**<filename column value*/

    Document(int id, std::string name);
};
