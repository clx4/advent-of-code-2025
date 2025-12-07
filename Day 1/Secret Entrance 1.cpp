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
        char direction = line[0];
        int distance = stoi(line.substr(1));
        // Add or subtract number and modulo
        if (direction == 'L') dial = (dial - distance) % 100;
        else dial = (dial + distance) % 100;
        // If its zero add to total count
        if (dial == 0) zero_count++;
    }

    // Return total count
    cout << zero_count << endl;
    
    file.close();
    return 0;
}
