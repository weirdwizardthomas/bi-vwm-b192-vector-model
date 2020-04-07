#include "Database.h"

using namespace std;

Database::Database(const string &path)
    : db(path) {}

vector<Document> Database::getDocumentsCollection() {
    SQLite::Statement query(db, "SELECT id, filename FROM Document");

    vector<Document> result;

    while (query.executeStep())
        result.emplace_back(query.getColumn("id"), query.getColumn("filename"));

    return result;
}

Document Database::getDocumentByID(int id) {
    SQLite::Statement query(db, "SELECT filename FROM Document WHERE id = :document_id");
    query.bind(":document_id", id);
    query.executeStep();

    return {id, query.getColumn("filename")};
}

vector<string> Database::getTermsByDocumentID(int document_id) {
    vector<string> terms;  
    SQLite::Statement query(db, "SELECT Term.value FROM Term "
                                "JOIN TermDocumentOccurrence ON Term.id = TermDocumentOccurrence.Term_id "
                                "WHERE TermDocumentOccurrence.Document_id = :id");
    query.bind(":id", document_id);

    while(query.executeStep())
        terms.emplace_back(query.getColumn("value"));

    return terms;
}
