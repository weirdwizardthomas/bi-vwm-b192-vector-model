#include "Terms.h"

Terms::Terms(const std::string &path)
        : db(path) {}

std::vector<std::string> Terms::getTermsByDocumentID(int document_id) {
    std::vector<std::string> terms;  
    SQLite::Statement query(db, "SELECT Term.value FROM Term "
                                "JOIN TermDocumentOccurrence ON Term.id = TermDocumentOccurrence.Term_id "
                                "WHERE TermDocumentOccurrence.Document_id = :id");
    query.bind(":id", document_id);

    while(query.executeStep())
        terms.emplace_back(query.getColumn("value"));

    return terms;
}
