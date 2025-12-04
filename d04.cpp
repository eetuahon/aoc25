#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>

using namespace std;

vector<string> readfile() {
    ifstream filename("input04");
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

int countNeighbours(vector<vector<char>>& m, int r, int c) {
    int count = 0;
    size_t mr = m.size();
    size_t mc = m[0].size();
    if (r > 0 && m[r-1][c] == '@') {
        count++;
    }
    if (r > 0 && c > 0 && m[r-1][c-1] == '@') {
        count++;
    }
    if (r > 0 && c < mc - 1 && m[r-1][c+1] == '@') {
        count++;
    }
    if (c < mc - 1 && m[r][c+1] == '@') {
        count++;
    }
    if (c > 0 && m[r][c-1] == '@') {
        count++;
    }
    if (r < mr - 1 && c > 0 && m[r+1][c-1] == '@') {
        count++;
    }
    if (r < mr - 1 && m[r+1][c] == '@') {
        count++;
    }
    if (r < mr - 1 && c < mc -1 && m[r+1][c+1] == '@') {
        count++;
    }
    return count;
}

int part1(vector<string>& rows) {
    int sum = 0;
    vector<vector<char>> map;
    for (const string& row : rows) {
        vector<char> r(row.begin(), row.end());
        map.push_back(r);
    }
    size_t y = map.size();
    size_t x = map[0].size();
    for (size_t i = 0; i < y; i++) {
        for (size_t j = 0; j < x; j++) {
            if (map[i][j] != '@') {
                continue;
            }
            int count = countNeighbours(map, i, j);
            if (count < 4) {
                sum++;
            }
        }
    }
    return sum;
}

int part2(vector<string>& rows) {
    int sum = 0;
    vector<vector<char>> map;
    for (const string& row : rows) {
        vector<char> r(row.begin(), row.end());
        map.push_back(r);
    }
    size_t y = map.size();
    size_t x = map[0].size();
    int removed;
    do {
        vector<tuple<int, int>> removes;
        for (size_t i = 0; i < y; i++) {
            for (size_t j = 0; j < x; j++) {
                if (map[i][j] != '@') {
                    continue;
                }
                int count = countNeighbours(map, i, j);
                if (count < 4) {
                    tuple<int, int> coord(j, i);
                    removes.push_back(coord);
                }
            }
        }
        removed = removes.size();
        sum += removed;
        for (const tuple<int, int> t : removes) {
            int j = get<0>(t);
            int i = get<1>(t);
            map[i][j] = '.';
        }
    } while (removed != 0);
    
    return sum;
}

int main() {
    vector<string> strs = readfile();
    int c = part1(strs);
    cout << c << endl;
    c = part2(strs);
    cout << c << endl;
    return 0;
}