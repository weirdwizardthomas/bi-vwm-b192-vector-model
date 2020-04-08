#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WMenu.h>
#include <Wt/WBreak.h>
#include <Wt/WPushButton.h>

#include <fstream>
#include <vector>

#include "./../util/ArgumentParser.h"
#include "./../calculation/Query.h"
#include "./../calculation/Space.h"
#include "./../calculation/Computor.h"
#include "./../util/QueryJSONParser.h"
#include "./../util/InvertedIndexJSONParser.h"
#include "./../database/Database.h"

#include "MainPage.h"

MainPage::MainPage(const Wt::WEnvironment& env)
    : Wt::WApplication(env)
{
  Space space(InvertedIndexJSONParser("./../../data/persistence/invertedList.json").parse());
  Database database("./../../data/persistence/docs_and_terms.db");
  auto availableDocuments = database.getDocumentsCollection();

  auto container = root()->addWidget(Wt::cpp14::make_unique<Wt::WContainerWidget>());
  auto buttonPtr = Wt::cpp14::make_unique<Wt::WPushButton>("Show me more!");
  auto button = buttonPtr.get();

  container->addNew<Wt::WText>("<h1>Available books to display</h1>");

  Wt::WMenu *menu = container->addNew<Wt::WMenu>();
  menu->setStyleClass("navigation");
  for (int i = 0; i < 10; i++) {
    menu->addItem(getName(availableDocuments.at(i).name));
  }
  menu->select(0);

  container->addWidget(std::move(buttonPtr));

  button->clicked().connect([=] {
    displayDetail(space, container, availableDocuments.at(menu->currentIndex()).id);
  });
}

std::string MainPage::getName(const std::string & path)
{
  std::string name = path;
  size_t begin = name.find_last_of('/') + 1;
  name = name.substr(begin, name.find_last_of('.') - begin);
  name.replace(name.find("___"), 3, ": ");

  return name;
}

std::string MainPage::getDocument(const std::string & path)
{
  std::string content;
  std::ifstream file(path);
  content.assign((std::istreambuf_iterator<char>(file)),
                 (std::istreambuf_iterator<char>()   ));
  file.close();

  return content;
}

void MainPage::displayDetail(Space space, Wt::WContainerWidget * container, int document_id)
{
  // deletes everything from current container
  container->clear();
  
  // udelat to lepe, aby tu nemusely byt cesty napevno..
  Database database("./../../data/persistence/docs_and_terms.db");
  Document document = database.getDocumentByID(document_id);

  // threshold je nyni nastaven na -1 --> ve vysledku budou i uplne rozdilne dokumenty
  Query query(space.getTermsAndWeightsByID(database, document.id), -1);
  auto result = Computor(space, query).compute(database);

  // dodelat proklikavani na zobrazene podobne dokumenty
  for (size_t i = 0; i < 10 && i < result.size(); i++) {
    container->addNew<Wt::WText>("Document ID: " + std::to_string(result.at(i).first) + "; relevance: " + std::to_string(result.at(i).second));
    container->addNew<Wt::WBreak>();
  }

  container->addNew<Wt::WText>("<h1>" + getName(document.name) + "</h1>");
  auto text = Wt::cpp14::make_unique<Wt::WText>();
  text->setTextFormat(Wt::TextFormat::Plain);
  text->setText(getDocument(document.name));
  container->addWidget(std::move(text));
}
