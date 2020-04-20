#pragma once

#include <SQLiteCpp/SQLiteCpp.h>
#include <vector>
#include <map>
#include <string>

#include "Document.h"

/**
 * A class that handles fetching data from database
 */
class Database {
private:
    SQLite::Database db; /**< Database connection */

public:
    explicit Database(const std::string &path);

    /**
     * Fetches the entire table Document
     * @return Vector with all rows of table Document, sorted by ID
     */
    std::vector<Document> getDocumentsCollection();

    /**
     * Fetches a single Document row with a specific ID
     * @param id ID of the row to fetch
     * @return Document row with ID equal to ID
     */
    Document getDocumentByID(int id);

    /**
     * @brief Finds all terms and their weights from specified document
     * @param document_id Document's ID to process
     * @return Map with terms as keys and weights as their values
     */
    std::map<std::string, double> getTermsAndWightsByDocumentID(int document_id);

    /**
     * @brief Computes size of vector for every document in database
     * @return Map with document_id as key and size of vector as value
     */
    std::map<int, double> getVectorSizes();
};
