#pragma once

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <vector>
#include <string>

#include "./../database/Database.h"
#include "./../database/Document.h"
#include "./../calculation/Space.h"

class MainPage : public Wt::WApplication
{
public:
    MainPage(const Wt::WEnvironment& env);

private:
    Database database;
    Space space;
    std::vector<Document> availableDocuments;
    Wt::WContainerWidget * container;

    /**
     * @brief Gets the name of the document from it's path
     * @param path Path to the document
     * @return String with name of the document
     */
    std::string getName(const std::string & path);

    /**
     * @brief Gets the content of the document
     * @param path Path to the document
     * @return String with document's content
     */
    std::string getContent(const std::string & path);

    /**
     * @brief Displays main page with menu
     */    
    void displayMainPage();

    /**
     * @brief Displays page with document content and similar documents
     * @param document_id ID of document to display
     */
    void displayDetail(int document_id);
};
