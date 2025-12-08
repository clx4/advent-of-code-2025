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
    string line;

    // Parse ingredient ID ranges
    while (getline(file, line) && !line.empty()) {
        size_t pos = line.find('-');
        long long min = stoll(line.substr(0, pos));
        long long max = stoll(line.substr(pos + 1));
        id_ranges.emplace_back(min, max);
    }

    // Sort the ranges
    sort(id_ranges.begin(), id_ranges.end());

    // Merge ingredient ID ranges
    vector<pair<long long, long long>> merged_ranges;
    merged_ranges.push_back(id_ranges[0]);

    for (size_t i = 1; i < id_ranges.size(); i++) {
        auto& last = merged_ranges.back();
        const auto& curr = id_ranges[i];

        if (last.second >= curr.first) {
            last.second = max(curr.second, last.second);
        } else {
            merged_ranges.push_back(curr);
        }
    }

    // Sum fresh ingredients
    long long fresh_ingredients = 0;
    for (const auto& range : merged_ranges) {
        fresh_ingredients += range.second - range.first + 1;
    }
    
    cout << fresh_ingredients << endl;
}
