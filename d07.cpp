#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>

using namespace std;

vector<string> readfile() {
    ifstream filename("input07");
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

vector<vector<char>> square(vector<string>& rows) {
    vector<vector<char>> map;
    for (const string& row : rows) {
        map.push_back(vector<char>(row.begin(),row.end()));
    }
    return map;
}

long long part1(vector<vector<char>>& sq) {
    long long count = 0;
    size_t rows = sq.size();
    int start = distance(sq[0].begin(), find(sq[0].begin(), sq[0].end(), 'S'));
    set<int> flows = {start};
    for (size_t i = 1; i < sq.size(); i++) {
        set<int> nf;
        for (const int& f : flows) {
            if (sq[i][f] == '^') {
                nf.insert(f-1);
                nf.insert(f+1);
                count++;
            } else {
                nf.insert(f);
            }
        }
        flows = nf;
    }
    return count;
}

long long part2(vector<vector<char>>& sq) {
    long long count = 0;
    int rows = sq.size();
    int cols = sq[0].size();
    vector<vector<long>> counter(rows, vector<long>(cols, 0l));
    int start = distance(sq[0].begin(), find(sq[0].begin(), sq[0].end(), 'S'));
    set<int> flows = {start};
    counter[0][start] = 1l;
    for (size_t i = 1; i < sq.size(); i++) {
        set<int> nf;
        for (const int& f : flows) {
            long old = counter[i-1][f];
            if (sq[i][f] == '^') {
                nf.insert(f-1);
                nf.insert(f+1);
                counter[i][f-1] += old;
                counter[i][f+1] += old;
            } else {
                nf.insert(f);
                counter[i][f] += old;
            }
        }
        flows = nf;
    }
    for (const long& i : counter[rows-1]) {
        count += i;
    }
    return count;
}

int main() {
    vector<string> strs = readfile();
    vector<vector<char>> sq = square(strs);
    long long c = part1(sq);
    cout << c << endl;
    c = part2(sq);
    cout << c << endl;
    return 0;
}