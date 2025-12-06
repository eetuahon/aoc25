#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

vector<string> readfile() {
    ifstream filename("input06");
    vector<string> vs;
    if (!filename.is_open()) {
        return vs;
    }
    string line;
    while (getline(filename, line)) {
        vs.push_back(line);
    }
    return vs;
}

vector<vector<string>> square(vector<string>& rows) {
    vector<vector<string>> sq;
    for (const string& row : rows) {
        stringstream ss(row);
        string temp;
        vector<string> r;
        while(ss >> temp) {
            r.push_back(temp);
        }
        sq.push_back(r);
    }
    return sq;
}

vector<vector<char>> square2(vector<string>& rows) {
    vector<vector<char>> sq;
    for (const string& row : rows) {
        sq.push_back(vector<char>(row.begin(), row.end()));
    }
    return sq;
}

long long part1(vector<vector<string>>& sq) {
    long long count = 0;
    size_t rows = sq.size();
    size_t cols = sq[0].size();
    for (size_t i = 0; i < cols; i++) {
        long long col;
        string op = sq[rows-1][i];
        if (op == "+") {
            col = 0;
        } else {
            col = 1;
        }
        for (size_t j = 0; j < rows - 1; j++) {
            int val = stoi(sq[j][i]);
            if (op == "+") {
                col += val;
            } else {
                col *= val;
            }
        }
        count += col;
    }
    return count;
}

long long part2(vector<vector<char>>& sq) {
    long long sum = 0;
    size_t len = sq[0].size();
    size_t rows = sq.size();
    vector<int> nums;
    char op;
    for (int i = len - 1; i >= 0; i--) {
        string col;
        for (int j = 0; j < rows; j++) {
            char ch = sq[j][i];
            if (ch == '+') {
                op = '+';
            } else if (ch == '*') {
                op = '*';
            } else {
                col += ch;
            }
        }
        if (all_of(col.begin(), col.end(), ::isspace)) {
            nums.clear();
            op = '?';
            continue;
        }
        nums.push_back(stoi(col));
        long block;
        if (op == '+') {
            block = 0;
            for (int& n : nums) {
                block += n;
            }
            sum += block;
        } else if (op == '*') {
            block = 1;
            for (int& n : nums) {
                block *= n;
            }
            sum += block;
        }
    }
    return sum;
}

int main() {
    vector<string> strs = readfile();
    vector<vector<string>> sq = square(strs);
    long long c = part1(sq);
    cout << c << endl;
    vector<vector<char>> sq2 = square2(strs);
    c = part2(sq2);
    cout << c << endl;
    return 0;
}