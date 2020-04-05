#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WMenu.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WPushButton.h>

#include <fstream>
#include <vector>

#include "./../util/ArgumentParser.h"
#include "./../calculation/Query.h"
#include "./../calculation/Space.h"
#include "./../calculation/Computor.h"
#include "./../util/QueryJSONParser.h"
#include "./../util/InvertedIndexJSONParser.h"
#include "./../database/DocumentCollection.h"
#include "./../database/Document.h"

#include "MainPage.h"

MainPage::MainPage(const Wt::WEnvironment& env)
    : Wt::WApplication(env)
{
  Space space(InvertedIndexJSONParser("./../../data/persistence/invertedList.json").parse());
  DocumentCollection collection("./../../data/persistence/docs_and_terms.db");
  auto availableDocuments = collection.fetchCollection();

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
    displayDetail(container, availableDocuments.at(menu->currentIndex()).name);
  });
}

std::string MainPage::getName(const std::string & path)
{
  std::string name = path;
  name = name.substr(name.find_last_of('/') + 1);
  name = name.substr(0, name.find_last_of('.'));
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

  encode(content);

  size_t start_pos = 0;
  while((start_pos = content.find('\n', start_pos)) != std::string::npos) {
    content.replace(start_pos, 1, "<br/>");
    start_pos += 5;
  }

  return content;
}

void MainPage::encode(std::string & data) {
    std::string buffer;
    buffer.reserve(data.size());
    for(size_t pos = 0; pos != data.size(); ++pos) {
        switch(data[pos]) {
            case '&':  buffer.append("&amp;");       break;
            case '\"': buffer.append("&quot;");      break;
            case '\'': buffer.append("&apos;");      break;
            case '<':  buffer.append("&lt;");        break;
            case '>':  buffer.append("&gt;");        break;
            default:   buffer.append(&data[pos], 1); break;
        }
    }
    data.swap(buffer);
}

void MainPage::displayDetail(Wt::WContainerWidget * container, const std::string & path)
{
  // deletes everything from current container
  container->clear();
  // Show similar books
  container->addNew<Wt::WText>("<h1>" + getName(path) + "</h1>");
  container->addNew<Wt::WText>(getDocument(path));
}
