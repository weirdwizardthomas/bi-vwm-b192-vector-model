#pragma once

#include <Wt/WApplication.h>
#include <string>

#include "./../database/Document.h"

class MainPage : public Wt::WApplication
{
public:
    MainPage(const Wt::WEnvironment& env);

private:
    std::string getName(const std::string & path);
    std::string getDocument(const std::string & path);
    void displayDetail(Space space, const std::vector<Document> & availableDocuments, Wt::WContainerWidget * container, int document_id);
};
