#pragma once

#include <Wt/WApplication.h>
#include <string>

class MainPage : public Wt::WApplication
{
public:
    MainPage(const Wt::WEnvironment& env);

private:
    std::string getName(const std::string & path);
    std::string getDocument(const std::string & path);
    void encode(std::string & content);
};
