#include "Document.h"

#include <utility>

using namespace std;

Document::Document(const int id, string name) : id(id), name(move(name)) {}
