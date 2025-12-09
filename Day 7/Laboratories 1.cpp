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

    int num_splits = 0;

    // Draw the first emitted beam from the start position
    size_t start_location = manifold[0].find('S');
    manifold[1][start_location] = '|';

    // Starting from top, process incoming tachyon beams
    for (size_t i = 1; i < manifold.size() - 1; i++) {
        for (size_t j = 0; j < manifold[0].size(); j++) {
            if (manifold[i][j] == '|') {
                // Split the beam
                if (manifold[i + 1][j] == '^') {
                    manifold[i + 1][j - 1] = '|';
                    manifold[i + 1][j + 1] = '|';
                    num_splits++;
                } else {
                    manifold[i + 1][j] = '|';
                }
            }
        }
    }

    cout << num_splits << endl;
}
