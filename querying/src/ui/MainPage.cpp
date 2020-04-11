#include <Wt/WText.h>
#include <Wt/WMenu.h>
#include <Wt/WPushButton.h>

#include <fstream>

#include "./../calculation/Query.h"
#include "./../calculation/Computor.h"
#include "./../util/InvertedIndexJSONParser.h"
#include "MainPage.h"

MainPage::MainPage(const Wt::WEnvironment& env)
    : Wt::WApplication(env),
      database("./../../data/persistence/docs_and_terms.db"),
      space(InvertedIndexJSONParser("./../../data/persistence/invertedList.json").parse())
{
  availableDocuments = database.getDocumentsCollection();
  container = root()->addWidget(Wt::cpp14::make_unique<Wt::WContainerWidget>());
  displayMainPage();
}

void MainPage::displayMainPage()
{
  container->clear();

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
    displayDetail(availableDocuments.at(menu->currentIndex()).id);
  });
}

std::string MainPage::getName(const std::string & path)
{
  std::string name;
  size_t begin = path.find_last_of('/') + 1;
  name = path.substr(begin, path.find_last_of('.') - begin);
  name.replace(name.find("___"), 3, ": ");

  return name;
}

std::string MainPage::getContent(const std::string & path)
{
  std::string content;
  std::ifstream file(path);
  content.assign((std::istreambuf_iterator<char>(file)),
                 (std::istreambuf_iterator<char>()   ));
  file.close();

  return content;
}

void MainPage::displayDetail(int document_id)
{
  container->clear();

  Document document = database.getDocumentByID(document_id);
  auto mainPageButtonPtr = Wt::cpp14::make_unique<Wt::WPushButton>("Back to main page");
  auto mainPageButton = mainPageButtonPtr.get();
  auto nextBookButtonPtr = Wt::cpp14::make_unique<Wt::WPushButton>("Jump to selected book");
  auto nextBookButton = nextBookButtonPtr.get();

  // threshold je nyni nastaven na -1 --> ve vysledku budou i uplne rozdilne dokumenty
  Query query(database.getTermsAndWightsByDocumentID(document_id), -1);
  auto result = Computor(space, query).compute(database);

  container->addNew<Wt::WText>("<h1>The most similar books</h1>");
  
  Wt::WMenu *menu = container->addNew<Wt::WMenu>();
  menu->setStyleClass("similar navigation");
  for (size_t i = 0; i < 5 && i < result.size(); i++) {
    menu->addItem(getName(availableDocuments.at(result.at(i).first - 1).name) + " (similarity: " + std::to_string(result.at(i).second) + ")");
  }
  menu->select(0);

  container->addWidget(std::move(nextBookButtonPtr));
  container->addWidget(std::move(mainPageButtonPtr));

  container->addNew<Wt::WText>("<h1>" + getName(document.name) + "</h1>");
  auto text = Wt::cpp14::make_unique<Wt::WText>();
  text->setTextFormat(Wt::TextFormat::Plain);
  text->setText(getContent(document.name));
  container->addWidget(std::move(text));

  nextBookButton->clicked().connect([=] {
    if (menu->currentIndex() != 0)
      displayDetail(result.at(menu->currentIndex()).first);
  });

  mainPageButton->clicked().connect([=] {
    displayMainPage();
  });
}
