#include "Document.h"

#include <utility>

using namespace std;

Document::Document(int id, string name)
    : id(id), name(move(name)) {}
