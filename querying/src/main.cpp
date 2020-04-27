#include <iostream>

#include "calculation/Query.h"
#include "calculation/Space.h"
#include "calculation/Computor.h"
#include "database/Database.h"
#include "database/Document.h"
#include "ui/Page.h"
#include "util/ArgumentParser.h"
#include "util/InvertedIndexJSONParser.h"

using namespace std;
using namespace cxxopts;

std::unique_ptr<Wt::WApplication> createApplication(const Wt::WEnvironment& env)
{
    const string dbPath("./../../data/persistence/docs_and_terms.db");
    const string invertedIndexPath("./../../data/persistence/invertedList.json");

    auto app = Wt::cpp14::make_unique<Page>(env, dbPath, invertedIndexPath);
    app->setTitle("Querying: Vector model of information retrieval");
    app->useStyleSheet("https://fonts.googleapis.com/css?family=Open+Sans&display=swap");
    app->useStyleSheet("style.css");

    return std::move(app);
}

int main(int argc, char *argv[]) {

    return Wt::WRun(argc, argv, &createApplication);
    /*
    ArgumentParser argumentParser;
    switch (argumentParser.parse(argc, argv)) {
        case ArgumentParser::HELP: {
            cout << argumentParser.getHelp() << endl;
            return EXIT_SUCCESS;
        }
        case ArgumentParser::PARSE_FAILURE: {
            cout << "FAILURE" << endl;
            return EXIT_FAILURE;
        }
        case ArgumentParser::PARSE_SUCCESS: {
            break;
        }
    }
    //Initialise data
    Space space(InvertedIndexJSONParser(argumentParser.getIndexPath()).parse());
    DocumentCollection collection(argumentParser.getDatabasePath());

    auto availableDocuments = collection.fetchCollection();
    */
}
