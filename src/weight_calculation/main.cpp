#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include <SQLiteCpp/SQLiteCpp.h>
#include "../../lib/json.hpp"

using json = nlohmann::json;

bool calculateWeight(SQLite::Database & db, std::ofstream & ostream, const json & maxOccurrences, const std::string & term)
{
    uint32_t occurrences;
    double weight;
    maxOccurrences[term].get_to(occurrences);

    try
    {
        SQLite::Statement query(db, "SELECT * FROM TermDocumentOccurrence JOIN Term ON TermDocumentOccurrence.Term_id = Term.id WHERE Term.value = :term");
        query.bind(":term", term);

        ostream << term << ":";
        while(query.executeStep())
        {
            weight = query.getColumn("count").getInt() / (occurrences*1.0);
            ostream << " " << query.getColumn("Document_id") << " " << std::setprecision(20) << weight;
        }
        ostream << std::endl;
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
        SQLite::Database db("./../../../data/persistance/db", SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
        SQLite::Statement query(db, "SELECT value FROM Term");

        while (query.executeStep())
            if(!calculateWeight(db, ostream, maxOccurrences, query.getColumn("value")))
                return false;
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
    std::ifstream istream("./../../../data/persistance/most_frequent_words.json");
    std::ofstream ostream("./../../../data/persistance/invertedList.json");

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
