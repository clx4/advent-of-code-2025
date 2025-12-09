#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ifstream file("input.txt");
    string line;
    vector<string> manifold;
    
    while (getline(file, line)) {
        manifold.push_back(line);
    }

    // Keep track of number of timelines arriving at a point
    vector<long long> timelines(manifold[0].size());

    // Draw the first emitted beam from the start position
    size_t start_location = manifold[0].find('S');
    manifold[1][start_location] = '|';
    timelines[start_location] = 1;
    
    // Starting from top, process incoming tachyon beams
    for (size_t i = 1; i < manifold.size() - 1; i++) {
        for (size_t j = 0; j < manifold[0].size(); j++) {
            if (manifold[i][j] == '|') {
                // Split the timeline
                if (manifold[i + 1][j] == '^') {
                    manifold[i + 1][j - 1] = '|';
                    manifold[i + 1][j + 1] = '|';
                    timelines[j - 1] += timelines[j];
                    timelines[j + 1] += timelines[j];
                    timelines[j] = 0;
                } else {
                    manifold[i + 1][j] = '|';
                }
            }
        }
    }

    long long num_timelines = 0;
    for (const auto& count : timelines) {
        num_timelines += count;
    }

    cout << num_timelines << endl;
}
