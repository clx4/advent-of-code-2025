#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    // Read from file
    ifstream file("input.txt");
    string id_range;
    long long invalid_ids_sum = 0;

    // Split line by commas into ranges
    while (getline(file, id_range, ',')) {
        // Parse the range
        size_t pos = id_range.find('-');
        long long min = stoll(id_range.substr(0, pos));
        long long max = stoll(id_range.substr(pos + 1));

        // For each range iterate through all product IDs
        for (long long i = min; i <= max; i++) {
            string product_id = to_string(i);

            // Split product ID into sequences and compare
            size_t n = product_id.length();
            for (size_t j = n / 2; j > 0; j--) {
                if (n % j != 0) continue;

                // Check if every sequence is equal
                bool repeated = true;
                for (size_t k = 1; k < n / j; k++) {
                    if (product_id.substr(j * (k - 1), j) != product_id.substr(j * k, j)) {
                        repeated = false;
                        break;
                    }
                }

                if (repeated) {
                    invalid_ids_sum += i;
                    break;
                }
            }
        }
    }
    
    cout << invalid_ids_sum << endl;
    
    file.close();
    return 0;
}
