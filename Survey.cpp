#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>

// data point
struct DataPoint {
    double x1; 
    double x2; 
    std::string label;
};

// distance between two data points
double euclideanDistance(const DataPoint& a, const DataPoint& b) {
    return sqrt(pow(a.x1 - b.x1, 2) + pow(a.x2 - b.x2, 2));
}

// k-NN classification
std::string kNN(const std::vector<DataPoint>& data, const DataPoint& query, int k) {

    // distances
    std::vector<std::pair<double, std::string>> distances;

    // distance between query and each data
    for (const auto& point : data) {
        double distance = euclideanDistance(query, point);
        distances.push_back({distance, point.label});
    }

    // sort in ascending order
    std::sort(distances.begin(), distances.end());

    // votes for each class among the k nearest neighbors
    std::map<std::string, int> votes; 
    for (int i = 0; i < k; ++i) {
        votes[distances[i].second]++;
    }

    // class with the most votes
    int maxVotes = 0;
    std::string predictedLabel;
    for (const auto& pair : votes) {
        if (pair.second > maxVotes) {
            maxVotes = pair.second;
            predictedLabel = pair.first;
        }
    }

    return predictedLabel;
}

int main() {
    // sample data
    std::vector<DataPoint> data = {
        {5.1, 3.5, "Democrat"},
        {4.9, 3.0, "Democrat"},
        {6.2, 3.4, "Republican"},
        {5.9, 3.0, "Republican"},
        // Add more data points...
    };

    // input from the user
    double inputX1, inputX2;
    std::cout << "Enter feature 1: ";
    std::cin >> inputX1;
    std::cout << "Enter feature 2: ";
    std::cin >> inputX2;

    // query point
    DataPoint query = {inputX1, inputX2, ""};

    // k-NN classification with k=3
    int k = 3;
    std::string predictedAffiliation = kNN(data, query, k);

    // prediction
    std::cout << "Predicted political affiliation: " << predictedAffiliation << std::endl;

    return 0;
}
