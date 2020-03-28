#include <iostream>

#include "inverted_index/InvertedIndexJSONParser.h"
#include "query/Query.h"
#include "space/Space.h"
#include "Computor.h"

using namespace std;

int main() {
    Space space(InvertedIndexJSONParser("../../data/persistence/dummy.json").parse());

    Query query({
                        {"forest",   0.2},
                        {"mountain", 0.1},
                        {"nature",   0.8}}, 0.5);

    auto res = Computor(space, query).compute();
    for (const auto &[id, value]: res)
        cout << id << ":" << value << endl;
    return EXIT_SUCCESS;
}
