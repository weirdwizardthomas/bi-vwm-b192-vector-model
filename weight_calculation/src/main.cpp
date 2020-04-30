#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

#include <SQLiteCpp/SQLiteCpp.h>

void calculateWeight(SQLite::Database & db, std::ofstream & ostream, int termId, int documentsCount)
{
    int maxOccurrences;
    int numberOfDocuments;
    int documentId;
    double weight;

    SQLite::Statement termInfo(db, "SELECT (SELECT value FROM Term WHERE id = :termId) AS value, MAX(count) AS maxOccurrences, COUNT(Document_id) AS occursIn "
                                   "FROM TermDocumentOccurrence "
                                   "WHERE Term_id = :termId");
    termInfo.bind(":termId", termId);
    termInfo.executeStep();
    maxOccurrences = termInfo.getColumn("maxOccurrences");
    numberOfDocuments = termInfo.getColumn("occursIn");

    SQLite::Statement query(db, "SELECT Document_id, count FROM TermDocumentOccurrence WHERE Term_id = :termId ORDER BY Document_id ASC");
    query.bind(":termId", termId);

    ostream << "\"" << termInfo.getColumn("value") << "\":{";
    while(query.executeStep())
    {
        documentId = query.getColumn("Document_id");
        weight = (query.getColumn("count").getInt() / (double)maxOccurrences) * (log2((double)documentsCount/numberOfDocuments));
        ostream << "\"" << documentId << "\":" << std::setprecision(20) << weight << ",";

        SQLite::Statement update(db, "UPDATE TermDocumentOccurrence SET weight = :weight WHERE Document_id = :documentId AND Term_id = :termId");
        update.bind(":weight", weight);
        update.bind(":documentId", documentId);
        update.bind(":termId", termId);
        update.exec();
    }

    ostream.seekp(-1, std::ios_base::end);
    ostream << "},";
}

bool process(std::ofstream & ostream)
{
    try
    {
        SQLite::Database db("./../../data/persistence/docs_and_terms.db", SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
        SQLite::Transaction transaction(db);

        SQLite::Statement totalDocuments(db, "SELECT COUNT(id) AS totalDocuments FROM Document");
        totalDocuments.executeStep();
        int documentsCount = totalDocuments.getColumn("totalDocuments");

        ostream << "{";

        SQLite::Statement query(db, "SELECT id FROM Term");
        while (query.executeStep())
            calculateWeight(db, ostream, query.getColumn("id"), documentsCount);

        ostream.seekp(-1, std::ios_base::end);
        ostream << "}";
        transaction.commit();
    }

    catch(const std::exception& e)
    {
        std::cout << "SQLite exception: " << e.what() << std::endl;
        return false;
    }

    return true;
}

int main (void)
{
    std::ofstream ostream("./../../data/persistence/invertedList.json");

    if (ostream.fail())
    {
        std::cout << "Cannot create file 'invertedList.json'" << std::endl;
        return EXIT_FAILURE;
    }

    if (!process(ostream))
        return EXIT_FAILURE;

    ostream.close();
    if (ostream.fail())
    {
        std::cout << "Something went wrong during writing to output file 'invertedList.json'" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
