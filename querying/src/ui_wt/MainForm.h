#pragma once

#include <Wt/WApplication.h>
#include <string>

class MainForm : public Wt::WApplication
{
public:
    MainForm(const Wt::WEnvironment& env);

private:
    std::string getName(const std::string & path);
    std::string getDocument(const std::string & path);
    void encode(std::string & content);
};
