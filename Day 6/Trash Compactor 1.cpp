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
    vector<vector<int>> numbers;

    // Process the file so we can separate numbers and symbols
    while (getline(file, line)) {
        lines.push_back(line);
    }

    // Parse problems into a grid of numbers
    for (size_t i = 0; i < lines.size() - 1; i++) {
        numbers.emplace_back();

        stringstream ss(lines[i]);
        int num;

        while (ss >> num) {
            numbers.back().push_back(num);
        }
    }

    // Parse operators
    stringstream ss(lines.back());
    string operators;
    char operation;

    while (ss >> operation) {
        operators += operation;
    }

    vector<long long> answers(operators.size());

    // Process problems and store in answers
    for (size_t i = 0; i < numbers.size(); i++) {
        for (size_t j = 0; j < operators.size(); j++) {
            if (i == 0) {
                answers[j] = numbers[i][j];
            } else if (operators[j] == '*') {
                answers[j] *= numbers[i][j];
            } else {
                answers[j] += numbers[i][j];
            }
        }
    }

    // Add all the answers
    long long grand_total = 0;
    for (const auto& answer : answers) {
        grand_total += answer;
    }

    cout << grand_total << endl;
}
