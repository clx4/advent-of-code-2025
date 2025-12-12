#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int backtrack(int config, const int target, int idx, int num_presses, const vector<int>& buttons) {
    if (config == target) return num_presses;
    if (idx == buttons.size()) return buttons.size() + 1;

    config ^= buttons[idx];
    int a = backtrack(config, target, idx + 1, num_presses + 1, buttons);
    config ^= buttons[idx];
    int b = backtrack(config, target, idx + 1, num_presses, buttons);

    return min(a, b);
}

int main() {
    ifstream file("input.txt");
    string line;
    vector<int> machine_configs;
    vector<vector<int>> buttons;
    
    while (getline(file, line)) {
        istringstream ss(line);
        char c;

        // Skip the opening bracket
        ss >> c; 

        // Use bits to store indicator light configurations, with LSB as first light
        int machine_config = 0;
        int indicator_flag = 1;

        // Parse machine configuration
        while (ss >> c) {
            if (c == ']') break;

            if (c == '#') {
                machine_config |= indicator_flag;
            }

            indicator_flag <<= 1;
        }

        machine_configs.push_back(machine_config);

        vector<int> button_schematics;
        int button_wiring = 0;

        // Parse button presses
        while (ss >> c) {
            if (c == ',' || c == '(') continue;
            if (c == '{') break;

            if (c == ')') {
                button_schematics.push_back(button_wiring);
                button_wiring = 0;
            } else {
                button_wiring |= 1 << c - '0';
            }
        }

        buttons.push_back(button_schematics);
    }

    int total_fewest_presses = 0;

    // For every machine
    for (size_t i = 0; i < machine_configs.size(); i++) {
        const auto& machine_buttons = buttons[i];
        int fewest_presses = machine_buttons.size();

        // For every length of combos of button presses
        for (size_t j = 0; j < machine_buttons.size(); j++) {
            fewest_presses = backtrack(0, machine_configs[i], 0, 0, machine_buttons);
        }

        total_fewest_presses += fewest_presses;
    }
    
    cout << total_fewest_presses << endl;
}
