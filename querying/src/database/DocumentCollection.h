#ifndef QUERYING_DOCUMENTCOLLECTION_H
#define QUERYING_DOCUMENTCOLLECTION_H

#include <vector>
#include <string>

#include <lib/SQLiteCpp/include/SQLiteCpp/Database.h>
#include "Document.h"

/**
 * A class that handles fetching Document rows from the Document table
 */
class DocumentCollection {
private:
    SQLite::Database db; /**< Database connection */

public:
    explicit DocumentCollection(const std::string &path);

    /**
     * Fetches the entire table Document
     * @return Vector with all rows of table Document, sorted by ID
     */
    std::vector<Document> fetchCollection();

    /**
     * Fetches a single Document row with a specific ID
     * @param id ID of the row to fetch
     * @return Document row with ID equal to ID
     */
    Document getDocumentByID(int id);
};


#endif //QUERYING_DOCUMENTCOLLECTION_H
