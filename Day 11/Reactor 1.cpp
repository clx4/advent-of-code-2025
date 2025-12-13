#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

int backtrack(const unordered_map<string, vector<string>>& graph, const string& device, const string& target) {
    if (device == target) return 1;

    int num_paths = 0;
    for (const auto& output : graph.at(device)) {
        num_paths += backtrack(graph, output, target);
    }

    return num_paths;
}

int main() {
    ifstream file("input.txt");
    string line;
    unordered_map<string, vector<string>> device_outputs;

    while (getline(file, line)) {
        string device = line.substr(0, 3);

        istringstream ss(line.substr(5));
        string output;

        while (ss >> output) {
            device_outputs[device].push_back(output);
        }
    }

    int num_paths = backtrack(device_outputs, "you", "out");

    cout << num_paths << endl;
}
