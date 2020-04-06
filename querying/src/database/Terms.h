#pragma once

#include <SQLiteCpp/SQLiteCpp.h>
#include <vector>
#include <string>

/**
 * A class that handles fetching Terms from the TermDocumentOccurrence table
 */
class Terms {
private:
    SQLite::Database db; /**< Database connection */

public:
    explicit Terms(const std::string &path);

    /**
     * @brief Finds all terms from specified document
     * @param document_id to process
     * @return Vector with strings which are in specified document
     */
    std::vector<std::string> getTermsByDocumentID(int document_id);
};
