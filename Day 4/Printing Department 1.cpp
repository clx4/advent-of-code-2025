#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    // Read from file
    ifstream file("input.txt");
    vector<string> grid;
    int rolls = 0;

    // Build a 2d array to represent the grid
    string row;
    while (getline(file, row)) {
        grid.push_back(row);
    }

    file.close();

    // Traverse the grid
    for (size_t i = 0; i < grid.size(); i++) {
        for (size_t j = 0; j < grid[i].length(); j++) {
            if (grid[i][j] == '@') {
                // Check adjacent positions
                int adjacent_rolls = 0;
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        if (dx == 0 && dy == 0) continue;

                        int adj_i = i + dx, adj_j = j + dy;
                        if (adj_i < 0 || adj_i >= grid.size()) continue;
                        if (adj_j < 0 || adj_j >= grid[i].length()) continue;

                        if (grid[adj_i][adj_j] == '@') adjacent_rolls++;
                    }
                }

                if (adjacent_rolls < 4) rolls++;
            }
        }
    }

    cout << rolls << endl;
}
