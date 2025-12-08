#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    // Read from file
    ifstream file("input.txt");
    string bank;
    long long total_joltage = 0;
    int digits = 12;

    while (getline(file, bank)) {
        long long bank_joltage = 0;
        int index = -1;

        // Turn on the largest battery, then the largest after that, and so on...
        for (int i = 0; i < digits; i++) {
            long long battery = 0;
            
            for (int j = index + 1; j < bank.length() - (digits - i - 1); j++) {
                int joltage_rating = bank[j] - '0';
                if (battery < joltage_rating) {
                    battery = joltage_rating;
                    index = j;

                    if (joltage_rating == 9) break;
                }
            }

            // Compute maximum joltage
            bank_joltage = 10 * bank_joltage + battery;
        }

        // Add to total output joltage
        total_joltage += bank_joltage;
    }

    cout << total_joltage << endl;

    file.close();
}
