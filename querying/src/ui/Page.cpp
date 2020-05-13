#include <Wt/WCheckBox.h>
#include <Wt/WText.h>
#include <Wt/WMenu.h>
#include <Wt/WPushButton.h>

#include <fstream>

#include "./../calculation/Query.h"
#include "./../calculation/Computor.h"
#include "./../calculation/SequentialSearch.h"
#include "./../util/InvertedIndexJSONParser.h"
#include "Page.h"

Page::Page(const Wt::WEnvironment& env, const std::string & dbPath, const std::string & invertedIndexPath)
    : Wt::WApplication(env),
      database(dbPath),
      space(InvertedIndexJSONParser(invertedIndexPath).parse())
{
  availableDocuments = database.getDocumentsCollection();
  container = root()->addWidget(Wt::cpp14::make_unique<Wt::WContainerWidget>());
  displayMainPage();
}

void Page::displayMainPage()
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

  Wt::WCheckBox *checkBox = container->addNew<Wt::WCheckBox>("Search using inverted index");
  checkBox->setInline(false);
  checkBox->setChecked(true);

  container->addWidget(std::move(buttonPtr));

  button->clicked().connect([=] {
    displayDetail(availableDocuments.at(menu->currentIndex()).id, checkBox->isChecked());
  });
}

std::string Page::getName(const std::string & path)
{
  std::string name;
  size_t begin = path.find_last_of('/') + 1;
  name = path.substr(begin, path.find_last_of('.') - begin);
  name.replace(name.find("___"), 3, ": ");

  return name;
}

std::string Page::getContent(const std::string & path)
{
  std::string content;
  std::ifstream file(path);
  content.assign((std::istreambuf_iterator<char>(file)),
                 (std::istreambuf_iterator<char>()   ));
  file.close();

  return content;
}

void Page::displayDetail(int document_id, bool useInvertedIndex)
{
  container->clear();

  Document document = database.getDocumentByID(document_id);
  auto mainPageButtonPtr = Wt::cpp14::make_unique<Wt::WPushButton>("Back to main page");
  auto mainPageButton = mainPageButtonPtr.get();
  auto nextBookButtonPtr = Wt::cpp14::make_unique<Wt::WPushButton>("Jump to selected book");
  auto nextBookButton = nextBookButtonPtr.get();

  std::vector<std::pair<int, double>> result;

  if (useInvertedIndex) {
    // threshold je nyni nastaven na -1 --> ve vysledku budou i uplne rozdilne dokumenty
    Query query(database.getTermsAndWightsByDocumentID(document_id), -1);
    result = Computor(space, query).compute(database);
  }
  else {
    result = SequentialSearch::search(database, document_id);
  }

  container->addNew<Wt::WText>("<h1>The most similar books</h1>");
  
  Wt::WMenu *menu = container->addNew<Wt::WMenu>();
  menu->setStyleClass("similar navigation");
  for (size_t i = 0; i < 5 && i < result.size(); i++) {
    menu->addItem(getName(availableDocuments.at(result.at(i).first - 1).name) + " (similarity: " + std::to_string(result.at(i).second) + ")");
  }
  menu->select(0);

  Wt::WCheckBox *checkBox = container->addNew<Wt::WCheckBox>("Search using inverted index");
  checkBox->setInline(false);
  checkBox->setChecked(true);

  container->addWidget(std::move(nextBookButtonPtr));
  container->addWidget(std::move(mainPageButtonPtr));

  container->addNew<Wt::WText>("<h1>" + getName(document.name) + "</h1>");
  auto text = Wt::cpp14::make_unique<Wt::WText>();
  text->setTextFormat(Wt::TextFormat::Plain);
  text->setText(getContent(document.name));
  container->addWidget(std::move(text));

  nextBookButton->clicked().connect([=] {
    if (menu->currentIndex() != 0)
      displayDetail(result.at(menu->currentIndex()).first, checkBox->isChecked());
  });

  mainPageButton->clicked().connect([=] {
    displayMainPage();
  });
}
