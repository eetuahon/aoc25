#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

vector<string> readfile() {
    ifstream filename("input03");
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

long long part1(vector<string>& rows) {
    long long sum = 0;
    for (const string& row : rows) {
        vector<int> nums;
        for (char c : row) {
            nums.push_back(c - '0');
        }
        int a = -1;
        int b = -1;
        for (size_t i = 0; i <= nums.size() - 2; i++) {
            if (nums[i] > a) {
                a = nums[i];
                b = nums[i+1];
            } else if (nums[i+1] > b) {
                b = nums[i+1];
            }
        }
        sum += 10 * a + b;
    }
    return sum;
}

long long part2(vector<string>& rows) {
    long long sum = 0;
    for (const string& row : rows) {
        vector<int> nums;
        for (char c : row) {
            nums.push_back(c - '0');
        }
        int storage[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
        for (size_t i = 0; i <= nums.size() - 12; i++) {
            if (nums[i] > storage[0]) {
                storage[0] = nums[i];
                storage[1] = nums[i+1];
                storage[2] = nums[i+2];
                storage[3] = nums[i+3];
                storage[4] = nums[i+4];
                storage[5] = nums[i+5];
                storage[6] = nums[i+6];
                storage[7] = nums[i+7];
                storage[8] = nums[i+8];
                storage[9] = nums[i+9];
                storage[10] = nums[i+10];
                storage[11] = nums[i+11];
            } else if (nums[i+1] > storage[1]) {
                storage[1] = nums[i+1];
                storage[2] = nums[i+2];
                storage[3] = nums[i+3];
                storage[4] = nums[i+4];
                storage[5] = nums[i+5];
                storage[6] = nums[i+6];
                storage[7] = nums[i+7];
                storage[8] = nums[i+8];
                storage[9] = nums[i+9];
                storage[10] = nums[i+10];
                storage[11] = nums[i+11];
            } else if (nums[i+2] > storage[2]) {
                storage[2] = nums[i+2];
                storage[3] = nums[i+3];
                storage[4] = nums[i+4];
                storage[5] = nums[i+5];
                storage[6] = nums[i+6];
                storage[7] = nums[i+7];
                storage[8] = nums[i+8];
                storage[9] = nums[i+9];
                storage[10] = nums[i+10];
                storage[11] = nums[i+11];
            } else if (nums[i+3] > storage[3]) {
                storage[3] = nums[i+3];
                storage[4] = nums[i+4];
                storage[5] = nums[i+5];
                storage[6] = nums[i+6];
                storage[7] = nums[i+7];
                storage[8] = nums[i+8];
                storage[9] = nums[i+9];
                storage[10] = nums[i+10];
                storage[11] = nums[i+11];
            } else if (nums[i+4] > storage[4]) {
                storage[4] = nums[i+4];
                storage[5] = nums[i+5];
                storage[6] = nums[i+6];
                storage[7] = nums[i+7];
                storage[8] = nums[i+8];
                storage[9] = nums[i+9];
                storage[10] = nums[i+10];
                storage[11] = nums[i+11];
            } else if (nums[i+5] > storage[5]) {
                storage[5] = nums[i+5];
                storage[6] = nums[i+6];
                storage[7] = nums[i+7];
                storage[8] = nums[i+8];
                storage[9] = nums[i+9];
                storage[10] = nums[i+10];
                storage[11] = nums[i+11];
            } else if (nums[i+6] > storage[6]) {
                storage[6] = nums[i+6];
                storage[7] = nums[i+7];
                storage[8] = nums[i+8];
                storage[9] = nums[i+9];
                storage[10] = nums[i+10];
                storage[11] = nums[i+11];
            } else if (nums[i+7] > storage[7]) {
                storage[7] = nums[i+7];
                storage[8] = nums[i+8];
                storage[9] = nums[i+9];
                storage[10] = nums[i+10];
                storage[11] = nums[i+11];
            } else if (nums[i+8] > storage[8]) {
                storage[8] = nums[i+8];
                storage[9] = nums[i+9];
                storage[10] = nums[i+10];
                storage[11] = nums[i+11];
            } else if (nums[i+9] > storage[9]) {
                storage[9] = nums[i+9];
                storage[10] = nums[i+10];
                storage[11] = nums[i+11];
            } else if (nums[i+10] > storage[10]) {
                storage[10] = nums[i+10];
                storage[11] = nums[i+11];
            } else if (nums[i+11] > storage[11]) {
                storage[11] = nums[i+11];
            }
        }
        long long multiplier = 100000000000;
        for (const int& i : storage) {
            sum += multiplier * i;
            multiplier /= 10;
        }
    }
    return sum;
}

int main() {
    vector<string> strs = readfile();
    long long c = part1(strs);
    cout << c << endl;
    c = part2(strs);
    cout << c << endl;
    return 0;
}