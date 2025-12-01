#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<string> readfile() {
    ifstream filename("input01");
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

int part1(vector<string>& rows) {
    int c = 0;
    int place = 50;
    for (const string& row : rows) {
        int temp = stoi(row.substr(1));
        if (row[0] == 'L') {
            place -= temp;
        } else if (row[0] == 'R') {
            place += temp;
        }
        while (place < 0) {
            place += 100;
        } 
        while (place >= 100) {
            place -= 100;
        }
        if (place == 0) {
            c++;
        }
    }
    return c;
}

int part2(vector<string>& rows) {
    int c = 0;
    int place = 50;
    int tplace;
    for (const string& row : rows) {
        int temp = stoi(row.substr(1));
        int t2 = temp / 100;
        c += t2;
        temp -= t2 * 100;
        if (row[0] == 'L') {
            place -= temp;
        } else if (row[0] == 'R') {
            place += temp;
        }
        if (place < 0) {
            place += 100;
            if (tplace != 0) {
                c++;
            }
        } else if (place >= 100) {
            place -= 100;
            c++;
        } else if (place == 0) {
            c++;
        }
        tplace = place;
    }
    return c;
}

int main() {
    vector<string> strs = readfile();
    int c = part1(strs);
    cout << c << endl;
    c = part2(strs);
    cout << c << endl;
    return 0;
}