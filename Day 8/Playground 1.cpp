#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue>

using namespace std;

struct Vec3 {
    int x, y, z;
};

int main() {
    ifstream file("input.txt");
    string line;
    vector<Vec3> coordinates;

    // Parse input into list of vectors
    while (getline(file, line)) {
        istringstream ss(line);
        int x, y, z;
        char comma;
        ss >> x >> comma >> y >> comma >> z;
        coordinates.emplace_back(x, y, z);
    }

    // Euclidean distance helper
    auto distance_squared = [](const auto& a, const auto& b) {
        long long dx = a.x - b.x, dy = a.y - b.y, dz = a.z - b.z;
        return dx*dx + dy*dy + dz*dz;
    };

    // Get distance between every pair of junction boxes
    map<long long, pair<int, int>> pair_distances;
    for (size_t i = 0; i < coordinates.size(); i++) {
        for (size_t j = i + 1; j < coordinates.size(); j++) {
            long long dist = distance_squared(coordinates[i], coordinates[j]);
            pair_distances[dist] = {i, j};
        }
    }

    // Connect 1000 closest pairs
    unordered_map<int, vector<int>> circuits;
    auto it = pair_distances.begin();
    for (int i = 0; i < 1000 && it != pair_distances.end(); i++, it++) {
        circuits[it->second.first].push_back(it->second.second);
        circuits[it->second.second].push_back(it->second.first);
    }

    // Get circuit box sizes by traversing graph
    unordered_set<int> visited;
    vector<int> circuit_sizes;  // Could also use a min heap of size 3
    for (size_t i = 0; i < coordinates.size(); i++) {
        // Skip circuits we've visited or containing only a single box
        if (!circuits.contains(i)) continue;
        if (visited.contains(i)) continue;
        
        // BFS
        int circuit_size = 0;
        queue<int> q;
        q.push(i);
        visited.insert(i);

        while (!q.empty()) {
            const auto& curr = q.front();
            q.pop();

            circuit_size++;

            for (const auto& neighbor : circuits[curr]) {
                if (!visited.contains(neighbor)) {
                    q.push(neighbor);
                    visited.insert(neighbor);
                }
            }
        }

        circuit_sizes.push_back(circuit_size);
    }

    // Sort circuit sizes and multiply three largest
    sort(circuit_sizes.begin(), circuit_sizes.end(), greater<int>());
    int circuit_size_product = circuit_sizes[0] * circuit_sizes[1] * circuit_sizes[2];

    cout << circuit_size_product << endl;
}
