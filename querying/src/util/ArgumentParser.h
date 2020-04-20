#ifndef QUERYING_ARGUMENTPARSER_H
#define QUERYING_ARGUMENTPARSER_H

#include "../lib/cxxopts.hpp"

/**
 * A class that parses and sanitises arguments
 */
class ArgumentParser {
private:
    cxxopts::Options options; /**<Parses the arguments*/
    std::string databasePath; /**<Path to the project's database */
    std::string indexPath; /**<Path to the calculated inverted index list of terms/*/
public:
    static const int PARSE_SUCCESS = 0;
    static const int PARSE_FAILURE = 1;
    static const int HELP = 2;

    ArgumentParser();

    /**
     * Parses arguments
     * @param argc Argument count
     * @param argv Arguments
     * @return one of @see PARSE_SUCCESS, @see PARSE_FAILURE, @see HELP, depending on received arguments
     */
    int parse(int argc, char *argv[]);

    std::string getDatabasePath() const;

    std::string getIndexPath() const;

    std::string getHelp() const;
};


#endif //QUERYING_ARGUMENTPARSER_H
