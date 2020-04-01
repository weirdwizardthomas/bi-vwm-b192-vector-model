#include "DocumentCollection.h"
#include <SQLiteCpp/SQLiteCpp.h>

using namespace std;

DocumentCollection::DocumentCollection(const string &path)
        : db(path) {}

std::vector<Document> DocumentCollection::fetchCollection() {
    SQLite::Statement query(db, "SELECT id, filename FROM Document");

    vector<Document> result;

    while (query.executeStep())
        result.emplace_back(query.getColumn("id"), query.getColumn("filename"));

    return result;
}

Document DocumentCollection::getDocumentByID(int id) {
    SQLite::Statement query(db, "SELECT filename FROM Document WHERE id = :document_id");
    query.bind(":document_id", id);
    query.executeStep();

    return {id, query.getColumn("filename")};
}
