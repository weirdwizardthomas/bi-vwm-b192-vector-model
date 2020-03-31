#include <iostream>
#include <map>

#include <QApplication>
#include <src/util/ArgumentParser.h>

#include "calculation/Query.h"
#include "calculation/Space.h"
#include "calculation/Computor.h"
#include "util/QueryJSONParser.h"
#include "util/InvertedIndexJSONParser.h"
#include "src/ui/forms/mainform.h"
#include "src/database/DocumentCollection.h"
#include "src/database/Document.h"

using namespace std;
using namespace cxxopts;

int main(int argc, char *argv[]) {

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
    //Start UI
    QApplication application(argc, argv);

    MainForm mainForm;
    mainForm
            .setAvailableDocuments(availableDocuments)
            .setOpenedDocument(availableDocuments.front());
    mainForm.show();

    return QApplication::exec();
}

/*
int main(int argc, char **argv) {

    string queryPath;
    bool exit = false;
    double threshold;

    while (true) {
        cin >> exit;
        if (exit)
            break;

        cin >> queryPath >> threshold;
        Query query(QueryJSONParser(queryPath).parse(), threshold);
        auto res = Computor(space, query).compute();
     }


 }
*/
