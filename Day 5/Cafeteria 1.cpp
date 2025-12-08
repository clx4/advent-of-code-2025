#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Read from file
    ifstream file("input.txt");
    vector<pair<long long, long long>> id_ranges;
    vector<long long> available_ids;
    string line;

    // Parse ingredient ID ranges
    while (getline(file, line) && !line.empty()) {
        size_t pos = line.find('-');
        long long min = stoll(line.substr(0, pos));
        long long max = stoll(line.substr(pos + 1));
        id_ranges.emplace_back(min, max);
    }

    // Parse available ingredient IDs
    while (getline(file, line)) {
        available_ids.push_back(stoll(line));
    }

    // Sort the ranges
    sort(id_ranges.begin(), id_ranges.end());

    // Check which available IDs are within a range
    int fresh_ingredients = 0;
    for (auto& id : available_ids) {
        auto it = upper_bound(id_ranges.begin(), id_ranges.end(), id,
            [](long long val, const pair<long long, long long>& range) {
                return val < range.first;
            });

        while (it != id_ranges.begin()) {
            --it;
            if (id >= it->first && id <= it->second) {
                fresh_ingredients++;
                break;
            }
        }
    }
    
    cout << fresh_ingredients << endl;
}
