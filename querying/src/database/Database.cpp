#include "Database.h"

using namespace std;

Database::Database(const string &path)
    : db(path) {}

vector<Document> Database::getDocumentsCollection() {
    SQLite::Statement query(db, "SELECT id, filename FROM Document ORDER BY filename ASC");

    vector<Document> result;

    while (query.executeStep())
        result.emplace_back(query.getColumn(0), query.getColumn(1));

    return result;
}

Document Database::getDocumentByID(int id) {
    SQLite::Statement query(db, "SELECT filename FROM Document WHERE id = :document_id");
    query.bind(":document_id", id);
    query.executeStep();

    return {id, query.getColumn(0)};
}

map<string, double> Database::getTermsAndWightsByDocumentID(int documentID) {
    map<string, double> termsAndWeights;
    SQLite::Statement query(db, "SELECT Term.value, TermDocumentOccurrence.weight FROM Term "
                                "JOIN TermDocumentOccurrence ON Term.id = TermDocumentOccurrence.Term_id "
                                "WHERE TermDocumentOccurrence.Document_id = :documentID");
    query.bind(":documentID", documentID);

    while(query.executeStep())
        termsAndWeights[query.getColumn(0)] = query.getColumn(1);

    return termsAndWeights;
}

map<int, double> Database::getVectorSizes() {
    map<int, double> vectorSizes;
    SQLite::Statement query(db, "SELECT Document_id, weight FROM TermDocumentOccurrence");

    while(query.executeStep()) {
        double tmp = query.getColumn(1);
        vectorSizes[query.getColumn(0)] += tmp * tmp;
    }

    return vectorSizes;
}

vector<pair<double, double>> Database::getTermsWeights(int queryDocumentID, int documentID) {
    vector<pair<double, double>> results;
    SQLite::Statement query(db, "SELECT Term_id AS Term_id_1, weight AS weight_1, weight_2 "
                                "FROM TermDocumentOccurrence "
                                "JOIN (SELECT Term_id AS Term_id_2, weight AS weight_2 "
                                      "FROM TermDocumentOccurrence "
                                      "WHERE Document_id = :documentID) "
                                "ON Term_id_1 = Term_id_2 "
                                "WHERE Document_id = :queryDocumentID");
    query.bind(":queryDocumentID", queryDocumentID);
    query.bind(":documentID", documentID);

    while(query.executeStep())
        results.emplace_back(make_pair(query.getColumn("weight_1"), query.getColumn("weight_2")));

    return results;
}
