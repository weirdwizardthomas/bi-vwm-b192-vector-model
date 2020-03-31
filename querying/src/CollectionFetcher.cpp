#include "CollectionFetcher.h"
#include <SQLiteCpp/SQLiteCpp.h>

using namespace std;

vector<string> CollectionFetcher::fetchCollection(const string &databasePath) {
    SQLite::Database db(databasePath);
    SQLite::Statement query(db, "SELECT filename FROM Document");

    vector<string> result;

    while (query.executeStep())
        result.emplace_back(query.getColumn(0));


    return result;
}
