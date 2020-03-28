#ifndef QUERYING_EXCEPTIONS_H
#define QUERYING_EXCEPTIONS_H

#include <exception>
#include <string>

class EndOfIndexException : public std::exception {
};

class IDNotFoundException : public std::exception {
};

#endif //QUERYING_EXCEPTIONS_H
