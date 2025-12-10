#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ifstream file("input.txt");
    string line;
    vector<pair<long long, long long>> tile_locations;
    
    // Get a list of grid locations from the input
    while (getline(file, line)) {
        size_t pos = line.find(',');
        auto x = stoll(line.substr(0, pos));
        auto y = stoll(line.substr(pos + 1));
        tile_locations.emplace_back(x, y);
    }

    // Make every possible rectangle
    long long largest_area = 0;
    for (size_t i = 0; i < tile_locations.size(); i++) {
        for (size_t j = i + 1; j < tile_locations.size(); j++) {
            auto width = abs(tile_locations[i].first - tile_locations[j].first) + 1;
            auto height = abs(tile_locations[i].second - tile_locations[j].second) + 1;
            largest_area = max(width * height, largest_area);
        }
    }

    cout << largest_area << endl;
}
