#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

int count_paths(const unordered_map<string, vector<string>>& device_outputs, const string& device, const string& target) {
    if (device == target) return 1;

    int num_paths = 0;
    for (const auto& output : device_outputs.at(device)) {
        num_paths += count_paths(device_outputs, output, target);
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

    const int num_paths = count_paths(device_outputs, "you", "out");

    cout << num_paths << endl;
}
