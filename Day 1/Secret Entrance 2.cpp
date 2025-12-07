#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    // Read from file
    ifstream file("input.txt");
    string line;
    int zero_count;
    
    int dial = 50;
    while (getline(file, line)) {
        // Split line into direction and distance
        int direction = line[0] == 'L' ? -1 : 1;
        int distance = stoi(line.substr(1));

        // Shitty ass brute force solution
        for (int i = 0; i < distance; i++) {
            dial = (dial + direction) % 100;

            // If its zero add to total count
            if (dial == 0) zero_count++;
        }
    }

    // Return total count
    cout << zero_count << endl;
    
    file.close();
    return 0;
}
