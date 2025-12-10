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

    // Connect closest pairs until we form a single circuit
    unordered_map<int, vector<int>> circuits;
    auto it = pair_distances.begin();
    int num_circuits = 0;
    pair<int, int> last_junction_indices;

    while(num_circuits != 1) {
        ++it;

        circuits[it->second.first].push_back(it->second.second);
        circuits[it->second.second].push_back(it->second.first);
        last_junction_indices = it->second;

        // Get circuit box sizes by traversing graph
        num_circuits = 0;
        unordered_set<int> visited;
        for (size_t i = 0; i < coordinates.size(); i++) {
            // Skip circuits we've visited or containing only a single box
            if (!circuits.contains(i)) {
                num_circuits++;
                continue;
            }

            if (visited.contains(i)) continue;
            
            // BFS
            queue<int> q;
            q.push(i);
            visited.insert(i);

            while (!q.empty()) {
                const auto& curr = q.front();
                q.pop();

                for (const auto& neighbor : circuits[curr]) {
                    if (!visited.contains(neighbor)) {
                        q.push(neighbor);
                        visited.insert(neighbor);
                    }
                }
            }

            num_circuits++;
        }
    }

    long long last_boxes_product = (long long) coordinates[last_junction_indices.first].x * 
                                               coordinates[last_junction_indices.second].x;

    cout << last_boxes_product << endl;
}
