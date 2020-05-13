#include <algorithm>
#include <cmath>

#include "SequentialSearch.h"
#include "./../database/Document.h"

using namespace std;

vector<pair<int, double>> SequentialSearch::search(Database & database, int queryDocument) {
    vector<pair<int, double>> results;
    map<int, double> vectorSizes = database.getVectorSizes();

    vector<Document> availableDocuments = database.getDocumentsCollection();

    for (const Document & document : availableDocuments) {
        double result = 0, denominator = 0;

        vector<pair<double, double>> termsWeights = database.getTermsWeights(queryDocument, document.id);

        for (const pair<double, double> & record : termsWeights)
            result += record.first * record.second;

        denominator = sqrt(vectorSizes[queryDocument] * vectorSizes[document.id]);
        // Input should not be zero vector but if it is, do not divide and "just" return wrong result..
        if (denominator != 0)
            result = result / denominator;

        results.emplace_back(make_pair(document.id, result));
    }

    sort(results.begin(), results.end(), [] (const pair<int, double> & a, const pair<int, double> & b)
                                            { return a.second > b.second; });

    return results;
}
