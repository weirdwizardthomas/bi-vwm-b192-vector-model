#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WMenu.h>
#include <Wt/WStackedWidget.h>

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

#include "MainForm.h"

MainForm::MainForm(const Wt::WEnvironment& env)
    : Wt::WApplication(env)
{
  Space space(InvertedIndexJSONParser("./../../data/persistence/invertedList.json").parse());
  DocumentCollection collection("./../../data/persistence/docs_and_terms.db");
  auto availableDocuments = collection.fetchCollection();

  auto container = root()->addWidget(Wt::cpp14::make_unique<Wt::WContainerWidget>());
  container->addNew<Wt::WText>("<h1>Choose document to display</h1><hr/>");

  auto contents = Wt::cpp14::make_unique<Wt::WStackedWidget>();

  Wt::WMenu *menu = container->addNew<Wt::WMenu>(contents.get());
  menu->setStyleClass("navigation");

  for (int i = 0; i < 10; i++)
  {
    std::string path = availableDocuments.at(i).name;
    menu->addItem(getName(path), Wt::cpp14::make_unique<Wt::WText>(getDocument(path)));
  }

  container->addWidget(std::move(contents));
}

std::string MainForm::getName(const std::string & path)
{
  std::string name = path;
  name = name.substr(name.find_last_of('/') + 1);
  name = name.substr(0, name.find_last_of('.'));
  name.replace(name.find("___"), 3, ": ");

  return name;
}

std::string MainForm::getDocument(const std::string & path)
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

void MainForm::encode(std::string & data) {
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
