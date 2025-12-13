#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>

using namespace std;

map<pair<string, int>, long long> memo;

long long count_paths(
    const unordered_map<string, vector<string>>& device_outputs, 
    const string& device, 
    const string& target, 
    int path_flags
) {
    if (device == target) return path_flags == 3;
    if (device == "dac") path_flags |= 1;
    if (device == "fft") path_flags |= 2;

    if (memo.contains({device, path_flags})) return memo[{device, path_flags}];

    long long num_paths = 0;
    for (const auto& output : device_outputs.at(device)) {
        num_paths += count_paths(device_outputs, output, target, path_flags);
    }

    // Memoize
    memo[{device, path_flags}] = num_paths;

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

    const long long num_paths = count_paths(device_outputs, "svr", "out", 0);

    cout << num_paths << endl;
}
