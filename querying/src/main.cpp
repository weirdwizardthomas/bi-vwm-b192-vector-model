#include <iostream>
#include <map>

#include <src/util/ArgumentParser.h>

#include "calculation/Query.h"
#include "calculation/Space.h"
#include "calculation/Computor.h"
#include "util/QueryJSONParser.h"
#include "util/InvertedIndexJSONParser.h"
#include "src/ui/Page.h"
#include "src/database/Database.h"
#include "src/database/Document.h"

using namespace std;
using namespace cxxopts;

std::unique_ptr<Wt::WApplication> createApplication(const Wt::WEnvironment& env)
{
  auto app = Wt::cpp14::make_unique<Page>(env);
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
