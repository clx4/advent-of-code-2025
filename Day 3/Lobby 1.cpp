#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    // Read from file
    ifstream file("input.txt");
    string bank;
    int total_joltage = 0;

    while (getline(file, bank)) {
        int first_battery = 0, second_battery = 0;
        int first_index = -1, second_index = -1;

        // Turn on the first largest battery
        for (int i = 0; i < bank.length() - 1; i++) {
            int joltage_rating = bank[i] - '0';
            if (first_battery < joltage_rating) {
                first_battery = joltage_rating;
                first_index = i;

                if (joltage_rating == 9) break;
            }
        }

        // Turn on the largest battery after this one
        for (int i = first_index + 1; i < bank.length(); i++) {
            int joltage_rating = bank[i] - '0';
            if (second_battery < joltage_rating) {
                second_battery = joltage_rating;
                second_index = i;

                if (joltage_rating == 9) break;
            }
        }

        // Compute maximum joltage and add to total output joltage
        total_joltage += 10 * first_battery + second_battery;
    }

    cout << total_joltage << endl;

    file.close();
}
