#ifndef QUERYING_EXCEPTIONS_H
#define QUERYING_EXCEPTIONS_H

#include <exception>
#include <string>

/**
 * An exception that is thrown when the end of an inverted index list is reached (list is exhausted)
 */
class EndOfIndexException : public std::exception {
};

/**
 * An exception that is thrown when a document ID cannot be found
 */
class IDNotFoundException : public std::exception {
};

#endif //QUERYING_EXCEPTIONS_H
