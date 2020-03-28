#include <iostream>

#include "inverted_index/InputParser.h"
#include "space/Query.h"
#include "space/Space.h"
#include "Computor.h"

using namespace std;

int main() {
    Space space(InputParser("../../data/persistence/dummy.json").getInvertedIndices());

    Query query({
                        {"forest",   0.2},
                        {"mountain", 0.1},
                        {"nature",   0.8}}, 0.5);

    auto res = Computor(space, query).compute();
    for (const auto &[id, value]: res)
        cout << id << ":" << value << endl;
    return EXIT_SUCCESS;
}
