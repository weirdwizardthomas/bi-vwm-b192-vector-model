#include <utility>
#include <vector>

#include "./../database/Database.h"

namespace SequentialSearch {

    /**
     * @brief Function used for sequential search
     * @param database Database connection
     * @param queryDocument ID of document which represents query
     */
    std::vector<std::pair<int, double>> search(Database & database, int queryDocument);
}
