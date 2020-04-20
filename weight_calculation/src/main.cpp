#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include <SQLiteCpp/SQLiteCpp.h>

#include "../lib/json.hpp"

using json = nlohmann::json;

bool calculateWeight(SQLite::Database & db, std::ofstream & ostream, const json & maxOccurrences, const std::string & term)
{
    uint32_t occurrences;
    double weight;
    maxOccurrences[term].get_to(occurrences);

    try
    {
        SQLite::Statement query(db, "SELECT TermDocumentOccurrence.Document_id, TermDocumentOccurrence.count, TermDocumentOccurrence.Term_id FROM TermDocumentOccurrence "
                                    "JOIN Term ON TermDocumentOccurrence.Term_id = Term.id "
                                    "WHERE Term.value = :term "
                                    "ORDER BY TermDocumentOccurrence.Document_id ASC");
        query.bind(":term", term);

        ostream << "\"" << term << "\":{";
        while(query.executeStep())
        {
            int document_id = query.getColumn("Document_id").getInt();
            weight = query.getColumn("count").getInt() / (occurrences*1.0);
            ostream << "\"" << document_id << "\":" << std::setprecision(20) << weight << ",";

            SQLite::Statement update(db, "UPDATE TermDocumentOccurrence SET weight = :weight "
                                         "WHERE Document_id = :document_id AND Term_id = :term_id");
            update.bind(":weight", weight);
            update.bind(":document_id", document_id);
            update.bind(":term_id", query.getColumn("Term_id").getInt());
            update.exec();
        }

        ostream.seekp(-1, std::ios_base::end);
        ostream << "},";
    }

    catch(const std::exception& e)
    {
        std::cout << "SQLite exception: " << e.what() << std::endl;
        return false;
    }

    return true;
}

bool process(std::ofstream & ostream, const json & maxOccurrences)
{
    try
    {
        SQLite::Database db("./../../data/persistence/docs_and_terms.db", SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
        SQLite::Statement query(db, "SELECT value FROM Term");

        ostream << "{";
        while (query.executeStep())
            if(!calculateWeight(db, ostream, maxOccurrences, query.getColumn("value")))
                return false;

        ostream.seekp(-1, std::ios_base::end);
        ostream << "}";
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
    std::ifstream istream("./../../data/persistence/most_frequent_words.json");
    std::ofstream ostream("./../../data/persistence/invertedList.json");

    if (istream.fail() || ostream.fail())
    {
        std::cout << "Cannot open/find file 'most_frequent_words.json' or cannot create file 'invertedList.json'" << std::endl;
        return EXIT_FAILURE;
    }

    json maxOccurrences;
    istream >> maxOccurrences;
    istream.close();

    if (istream.fail())
    {
        std::cout << "Something went wrong with file 'most_frequent_words.json'" << std::endl;
        return EXIT_FAILURE;
    }

    if (!process(ostream, maxOccurrences))
        return EXIT_FAILURE;

    ostream.close();
    if (ostream.fail())
    {
        std::cout << "Something went wrong during writing to output file 'invertedList.json'" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
