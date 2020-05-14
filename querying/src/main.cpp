#include <string>
#include <utility>

#include "ui/Page.h"

std::unique_ptr<Wt::WApplication> createApplication(const Wt::WEnvironment& env)
{
    const std::string dbPath("./../../data/persistence/docs_and_terms.db");
    const std::string invertedIndexPath("./../../data/persistence/invertedList.json");

    auto app = Wt::cpp14::make_unique<Page>(env, dbPath, invertedIndexPath);
    app->setTitle("Querying: Vector model of information retrieval");
    app->useStyleSheet("https://fonts.googleapis.com/css?family=Open+Sans&display=swap");
    app->useStyleSheet("style.css");

    return std::move(app);
}

int main(int argc, char *argv[]) {

    return Wt::WRun(argc, argv, &createApplication);
}
