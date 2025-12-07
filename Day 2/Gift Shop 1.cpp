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
            // Split product ID into half and compare
            string product_id = to_string(i);
            if (product_id.length() % 2 != 0) continue;
            size_t midpoint = product_id.length() / 2;
            if (product_id.substr(0, midpoint) == product_id.substr(midpoint)) invalid_ids_sum += i;
        }
    }
    
    cout << invalid_ids_sum << endl;
    
    file.close();
    return 0;
}
