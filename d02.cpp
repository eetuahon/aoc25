#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

vector<string> readfile() {
    ifstream filename("input02");
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
    stringstream ss(rows[0]);
    string pair;
    while (getline(ss, pair, ',')) {
        size_t i = pair.find('-');
        string a = pair.substr(0,i);
        string b = pair.substr(i+1);
        if (a.size() % 2 != 0 && b.size() % 2 != 0 && a.size() == b.size()) {
            continue;
        }
        long al, bl;
        if (a.size() == 1) {
            al = 1;
        } else {
            al = stoll(a.substr(0,a.size() / 2));
        }
        if (b.size() == 1) {
            continue;
        }
        bl = stoll(b.substr(0,b.size() / 2)) + 1;
        if (a.size() % 2 != 0 && a.size() != 1) {
            al = stoll("1" + string(a.size() / 2, '0'));
        }
        if (b.size() % 2 != 0) {
            bl = stoll(string(b.size() / 2, '9'));
        }
        for (long i = al; i <= bl; i++) {
            long long c = stoll(to_string(i) + to_string(i));
            if (c >= stoll(a) && c <= stoll(b)) {
                sum += c;
            }
        }
    }
    return sum;
}

long long part2(vector<string>& rows) {
    long long sum = 0;
    stringstream ss(rows[0]);
    string pair;
    vector<long long> found;
    while (getline(ss, pair, ',')) {
        size_t i = pair.find('-');
        string a = pair.substr(0,i);
        string b = pair.substr(i+1);
        for (int i = 1; i <= b.size() / 2; i++) {
            if (a.size() % i == 0) {
                long al = stol("1" + string(i-1, '0'));
                long bl = stol(string(i, '9'));
                for (long j = al; j <= bl; j++) {
                    string c = "";
                    for (int x = 0; x < (a.size() / to_string(j).size()); x++) {
                        c += to_string(j);
                    }
                    if (c.size() == 1) {
                        continue;
                    }
                    if (stoll(c) >= stoll(a) && stoll(c) <= stoll(b)) {
                        if (find(found.begin(), found.end(), stoll(c)) == found.end()) {
                            found.push_back(stoll(c));
                        }
                    }
                }
            }
            if (b.size() % i == 0 && a.size() != b.size()) {
                long al = stol("1" + string(i-1, '0'));
                long bl = stol(string(i, '9'));
                for (long j = al; j <= bl; j++) {
                    string c = "";
                    for (int x = 0; x < (b.size() / to_string(j).size()); x++) {
                        c += to_string(j);
                    }
                    if (c.size() == 1) {
                        continue;
                    }
                    if (stoll(c) >= stoll(a) && stoll(c) <= stoll(b)) {
                        if (find(found.begin(), found.end(), stoll(c)) == found.end()) {
                            found.push_back(stoll(c));
                        }
                    }
                }
            }
        }
    }
    
    for (const long long& v : found) {
        sum += v;
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