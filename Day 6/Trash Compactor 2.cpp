#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ifstream file("input.txt");
    string line;
    vector<string> lines;

    // Process the file
    while (getline(file, line)) {
        lines.push_back(line);
    }

    const size_t digit_rows = lines.size() - 1;
    const size_t columns = lines[0].size();

    long long grand_total = 0;
    bool is_multiplication = lines[digit_rows][0] == '*';
    long long answer = is_multiplication ? 1 : 0;

    // Process problems one-by-one
    for (size_t i = 0; i < columns; i++) {
        long long num = 0;
        for (size_t j = 0; j < digit_rows; j++) {
            if (lines[j][i] != ' ') num = num * 10 + lines[j][i] - '0';
        }

        if (num != 0) {
            // Add number to answer
            if (is_multiplication) {
                answer *= num;
            } else {
                answer += num;
            }
        } else {  // Column only of spaces, add answer & move to next problem
            grand_total += answer;
            is_multiplication = lines[digit_rows][i + 1] == '*';
            answer = is_multiplication ? 1 : 0;
        }
    }
    
    grand_total += answer;

    cout << grand_total << endl;
}
