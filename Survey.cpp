#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>
#include <unordered_map>

struct DataPoint {
    double x1;    // Feature 1
    double x2;    // Feature 2
    int president_opinion;    // Opinion on US President
    int healthcare_opinion;   // Opinion on healthcare
    int taxes_opinion;        // Opinion on taxes
    int gun_rights_opinion;   // Opinion on gun rights
    int voting_preference;    // Voting preference
    int life_start_opinion;   // Opinion on when life starts
    int pollution_opinion;    // Opinion on pollution
    int carpooling_opinion;   // Opinion on carpooling
    int fiscal_responsibility_opinion; // Opinion on fiscal responsibility
    std::string affiliation; // Political affiliation

    // Constructor
    DataPoint(double _x1, double _x2, int _president_opinion, int _healthcare_opinion, int _taxes_opinion, int _gun_rights_opinion, int _voting_preference, int _life_start_opinion, int _pollution_opinion, int _carpooling_opinion, int _fiscal_responsibility_opinion, const std::string& _affiliation)
        : x1(_x1), x2(_x2), president_opinion(_president_opinion), healthcare_opinion(_healthcare_opinion), taxes_opinion(_taxes_opinion), gun_rights_opinion(_gun_rights_opinion), voting_preference(_voting_preference), life_start_opinion(_life_start_opinion), pollution_opinion(_pollution_opinion), carpooling_opinion(_carpooling_opinion), fiscal_responsibility_opinion(_fiscal_responsibility_opinion), affiliation(_affiliation) {}

};


// Function to convert opinion and affiliation strings to integer values
int convertOpinionToValue(const std::string& opinionOrAffiliation) {
    // Map of opinion/affiliation strings to integer values
    std::unordered_map<std::string, int> valueMap = {
        // Affiliations
        {"Democrat", 0},
        {"Republican", 1},
        {"Green Party", 2},
        {"Independent", 3},
        // Add more mappings as needed...
    };

    // Look up the opinion/affiliation in the map
    auto it = valueMap.find(opinionOrAffiliation);
    if (it != valueMap.end()) {
        // Return the corresponding integer value
        return it->second;
    } else {
        // If opinion/affiliation is not found, return a default value or handle error
        return -1; // Default value, you can modify as needed
    }
}

// distance between two data points
double euclideanDistance(const DataPoint& a, const DataPoint& b) {
    return sqrt(pow(a.x1 - b.x1, 2) + pow(a.x2 - b.x2, 2));
}

std::string kNN(const std::vector<DataPoint>& data, const DataPoint& query, int k) {

    // distances
    std::vector<std::pair<double, std::string>> distances;

    // distance between query and each data
    for (const auto& point : data) {
        double distance = euclideanDistance(query, point);
        distances.push_back({distance, point.affiliation});
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
    std::string predictedAffiliation;
    for (const auto& pair : votes) {
        if (pair.second > maxVotes) {
            maxVotes = pair.second;
            predictedAffiliation = pair.first;
        }
    }

    return predictedAffiliation;
}

int main() {

    // Sample data
    std::vector<DataPoint> data;
    data.push_back(DataPoint(5.1, 3.5, 0, 1, 2, 3, 0, 1, 2, 3, 0, "Democrat"));
    data.push_back(DataPoint(4.9, 3.0, 1, 2, 3, 0, 1, 2, 3, 0, 1, "Republican"));
    data.push_back(DataPoint(6.2, 3.4, 2, 3, 0, 1, 2, 3, 0, 1, 2, "Green Party"));
    data.push_back(DataPoint(5.9, 3.0, 3, 0, 1, 2, 3, 0, 1, 2, 3, "Independent"));


    // Questions
    int president_opinion;
    int healthcare_opinion;
    int taxes_opinion;
    int gun_rights_opinion;
    int voting_preference;
    int life_start_opinion;
    int pollution_opinion;
    int carpooling_opinion;
    int fiscal_responsibility_opinion;
    std::string affiliation;        

    // Get user input
    std::cout << "Who would make the best US President? " << std::endl;
    std::cout << "0: Elizabeth Warren" << std::endl;
    std::cout << "1: Mitt Romney" << std::endl;
    std::cout << "2: Ralph Nader" << std::endl;
    std::cout << "3: Not sure/someone else" << std::endl;
    std::cin >> president_opinion;
    std::cout << "Which answer most closely resembles your opinion on healthcare?" << std::endl;
    std::cout << "0: Single-Payer" << std::endl;
    std::cout << "1: HSA" << std::endl;
    std::cout << "2: Universal" << std::endl;
    std::cout << "3: Not sure/something else" << std::endl;
    std::cin >> healthcare_opinion;
    std::cout << "How do you feel about taxes?" << std::endl;
    std::cout << "0: Necessary to support public programs" << std::endl;
    std::cout << "1: I prefer they go to defense spending" << std::endl;
    std::cout << "2: I prefer they help protect our environment" << std::endl;
    std::cout << "3: Not sure/something else" << std::endl;
    std::cin >> taxes_opinion;
    std::cout << "How do you feel about gun rights?" << std::endl;
    std::cout << "0: There should be increased regulations" << std::endl;
    std::cout << "1: There should be very little regulation" << std::endl;
    std::cout << "2: I'm indifferent" << std::endl;
    std::cout << "3: Not sure/something else" << std::endl;
    std::cin >> gun_rights_opinion;
    std::cout << "How do you feel about women's rights?" << std::endl;
    std::cout << "0: Define 'woman'" << std::endl;
    std::cout << "1: They can vote, now what do they want?" << std::endl;
    std::cout << "2: They should have rights!" << std::endl;
    std::cout << "3: Not sure/something else" << std::endl;
    std::cin >> voting_preference;
    std::cout << "When does life start?" << std::endl;
    std::cout << "0: When a woman decides it starts." << std::endl;
    std::cout << "1: When God said so" << std::endl;
    std::cout << "2: From seed" << std::endl;
    std::cout << "3: Not sure/something else" << std::endl;
    std::cin >> life_start_opinion;
    std::cout << "What are your thoughts on pollution? " << std::endl;
    std::cout << "0: It's ugly" << std::endl;
    std::cout << "1: Looks like money to me" << std::endl;
    std::cout << "2: It needs to stop or we are all going to die" << std::endl;
    std::cout << "3: Not sure/something else" << std::endl;
    std::cin >> pollution_opinion;
    std::cout << "How do you feel about carpooling?" << std::endl;
    std::cout << "0: More people should do it!" << std::endl;
    std::cout << "1: Sit next to other people? No, thanks" << std::endl;
    std::cout << "2: It needs to start or we are all going to die" << std::endl;
    std::cout << "3: Not sure/something else" << std::endl;
    std::cin >> carpooling_opinion;
    std::cout << "What best describes your ideas on fiscal responsibility?" << std::endl;
    std::cout << "0: Save, baby, save!" << std::endl;
    std::cout << "1: Spend, baby, spend" << std::endl;
    std::cout << "2: Plant trees like money grows on them!" << std::endl;
    std::cout << "3: Not sure/something else" << std::endl;
    std::cin >> fiscal_responsibility_opinion;
    // let the user know answer range
    std::cout << "Please type in one of the answers below:" << std::endl;
    std::cout << "Democrat" << std::endl;
    std::cout << "Republican" << std::endl;
    std::cout << "Green Party" << std::endl;
    std::cout << "Independent" << std::endl;
    std::cout << "What is your political affiliation? ";
    std::cin >> affiliation;
    
    // Query point
    DataPoint query(
        0.0, // x1 (double)
        0.0, // x2 (double)
        president_opinion,
        healthcare_opinion,
        taxes_opinion,
        gun_rights_opinion,
        voting_preference,
        life_start_opinion,
        pollution_opinion,
        carpooling_opinion,
        fiscal_responsibility_opinion,
        affiliation // Political affiliation (string)
    );


    // k-NN classification with k=3
    int k = 3;
    std::string predictedAffiliation = kNN(data, query, k);

    std::cout << "Predicted political affiliation: " << predictedAffiliation << std::endl;

    return 0;
}
