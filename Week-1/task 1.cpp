#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <limits>
#include <algorithm>

using namespace std;

const double WEIGHT_DIFFERENCE_THRESHOLD = 2.5;
const int NUM_PUPILS = 3;  // Set the fixed number of pupils to 3

bool validateWeight(double& weight) {
    if (weight < 0 || weight > 150) {
        cout << "Invalid weight. Please enter a valid weight between 0 and 150 kg." << endl;
        cin >> weight;
        return false;
    }
    return true;
}

bool validateName(string& name) {
    for (char c : name) {
        if (!isalpha(c) && c != ' ') {
            cout << "Invalid name. Please enter a valid name without special characters." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the input buffer
            getline(cin, name);
            return false;
        }
    }
    return true;
}

void inputAndStoreWeightsAndNames(vector<double>& weights, vector<string>& names) {
    for (int i = 0; i < NUM_PUPILS; i++) {
        string name;
        cout << "Enter the name of pupil " << i + 1 << ": ";
        getline(cin, name);

        while (!validateName(name)) {
            cout << "Invalid name. Please enter a valid name without special characters." << endl;
            cout << "Enter the name of pupil " << i + 1 << ": ";
            getline(cin, name);
        }

        double weight;
        cout << "Enter the weight of " << name << ": ";
        cin >> weight;

        while (!validateWeight(weight)) {
            cout << "Invalid weight. Please enter a valid weight between 0 and 150 kg." << endl;
            cout << "Enter the weight of " << name << ": ";
            cin >> weight;
        }

        weights.push_back(weight);
        names.push_back(name);

        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the input buffer
    }
}

void inputAndValidateFinalWeights(const vector<string>& initialNames, vector<double>& finalWeights) {
    for (int i = 0; i < NUM_PUPILS; i++) {
        string name;
        cout << "Enter the name for pupil " << i + 1 << " (matching the names entered initially): ";
        getline(cin, name);

        while (find(initialNames.begin(), initialNames.end(), name) == initialNames.end() || name.empty()) {
            cout << "Invalid name. Please enter a name that matches the names entered initially." << endl;
            cout << "Enter the name for pupil " << i + 1 << ": ";
            getline(cin, name);
        }

        double weight;
        cout << "Enter the weight of " << name << ": ";
        cin >> weight;

        while (!validateWeight(weight)) {
            cout << "Invalid weight. Please enter a valid weight between 0 and 150 kg." << endl;
            cout << "Enter the weight of " << name << ": ";
            cin >> weight;
        }

        finalWeights.push_back(weight);

        if (i < NUM_PUPILS - 1) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the input buffer
        }
    }
}

void calculateAndOutputWeightDifferences(const vector<double>& initialWeights, const vector<double>& finalWeights) {
    for (int i = 0; i < initialWeights.size(); i++) {
        double diff = finalWeights[i] - initialWeights[i];
        cout << "Pupil " << i + 1 << "'s weight changed by " << diff << " kg." << endl;
        if (abs(diff) > WEIGHT_DIFFERENCE_THRESHOLD) {
            string direction = diff > 0 ? "rise" : "fall";
            cout << "This is a " << direction << " of more than 2.5 kg." << endl;
        }
    }
}

int main() {
    vector<double> initialWeights, finalWeights;
    vector<string> names;

    inputAndStoreWeightsAndNames(initialWeights, names);

    cout << "Enter the weights again to calculate the difference:" << endl;
    inputAndValidateFinalWeights(names, finalWeights);

    cout << "The weight differences are:" << endl;
    calculateAndOutputWeightDifferences(initialWeights, finalWeights);

    return 0;
}
