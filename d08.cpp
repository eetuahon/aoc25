#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <tuple>
#include <unordered_map>
#include <set>
#include <queue>

using namespace std;

class Coord {
  public:
    int x;   
    int y;
    int z;
    Coord(int a, int b, int c) {
        x = a;
        y = b;
        z = c;
    };

    bool operator==(const Coord& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    bool operator<(const Coord& other) const {
        if (x + y + z != other.x + other.y + other.z) {
            return x + y + z < other.x + other.y + other.z;
        } else if (x != other.x) {
            return x < other.x;
        } else if (y != other.y) {
            return y < other.y;
        } else {
            return z < other.z;
        }
    }

    friend ostream& operator<<(ostream& os, const Coord& coord);
};

ostream& operator<<(ostream& os, const Coord& coord) {
    os << "(" << coord.x << ", " << coord.y << ", " << coord.z << ")";
    return os;
}

namespace std {
    template <>
    struct hash<Coord> {
        size_t operator()(const Coord& c) const {
            size_t h1 = hash<int>{}(c.x);
            size_t h2 = hash<int>{}(c.y);
            size_t h3 = hash<int>{}(c.z);
            return h1 ^ (h2 << 1) ^ (h3 << 2);
        }
    };
}

double distance(const Coord& a, const Coord& b) {
    long dx = a.x - b.x;
    long dy = a.y - b.y;
    long dz = a.z - b.z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}

vector<string> readfile() {
    ifstream filename("input08");
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

vector<Coord> coords(vector<string>& rows) {
    vector<Coord> coords;
    for (const string& row : rows) {
        stringstream ss(row);
        int a, b, c;
        char delimeter = ',';
        ss >> a >> delimeter >> b >> delimeter >> c;
        Coord co = Coord(a, b, c);
        coords.push_back(co);
    }
    return coords;
}

bool completeMap(unordered_map<Coord, vector<Coord>>& m) {
    Coord c = m.begin()->first;
    queue<Coord> workload;
    workload.push(c);
    set<Coord> seen = {c};
    while (!workload.empty()) {
        Coord cc = workload.front();
        workload.pop();
        for (const Coord& cn : m[cc]) {
            if (seen.insert(cn).second) {
                workload.push(cn);
            }
        }
    }
    return seen.size() == m.size();
}

long long part1(vector<Coord>& coords) {
    long long count = 1;
    size_t n = coords.size();
    vector<tuple<Coord, Coord, double>> dislist;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i+1; j < n; j++) {
            double d = distance(coords[i], coords[j]);
            tuple<Coord, Coord, double> coordpair(coords[i], coords[j], d);
            dislist.push_back(coordpair);
        }
    }
    sort(dislist.begin(), dislist.end(), [](const tuple<Coord, Coord, double>& a, const tuple<Coord, Coord, double>& b){
        return get<2>(a) < get<2>(b);
    });
    unordered_map<Coord, vector<Coord>> gr;
    size_t connections = 1000; // connect 1000 pairs as instructed
    for (int i = 0; i < connections; i++) {
        Coord fr = get<0>(dislist[i]);
        Coord sc = get<1>(dislist[i]);
        if (gr.find(fr) == gr.end()) {
            gr[fr] = vector<Coord>();
        }
        gr[fr].push_back(sc);
        if (gr.find(sc) == gr.end()) {
            gr[sc] = vector<Coord>();
        }
        gr[sc].push_back(fr);
    }
    set<Coord> seenAll;
    set<Coord> seen;
    vector<set<Coord>> groups;
    queue<Coord> workload;
    for (auto c : gr) {
        Coord co = c.first;
        vector<Coord> colist = c.second;
        if (seenAll.insert(co).second) {
            workload.push(co);
            while (!workload.empty()) {
                Coord cow = workload.front();
                seen.insert(cow);
                workload.pop();
                vector<Coord> checks = gr[cow];
                for (const Coord& cc : checks) {
                    if (seenAll.insert(cc).second) {
                        workload.push(cc);
                    }
                }
            }
            groups.push_back(seen);
            seen.clear();
        }
    }
    sort(groups.begin(), groups.end(), [](const set<Coord>& a, const set<Coord>& b) {
        return a.size() > b.size();
    });
    // Prod of 3 max requested
    for (int i = 0; i < 3; i++) {
        count *= groups[i].size();
    }
    return count;
}

long long part2(vector<Coord>& coords) {
    long long count = 1;
    size_t n = coords.size();
    vector<tuple<Coord, Coord, double>> dislist;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i+1; j < n; j++) {
            double d = distance(coords[i], coords[j]);
            tuple<Coord, Coord, double> coordpair(coords[i], coords[j], d);
            dislist.push_back(coordpair);
        }
    }
    sort(dislist.begin(), dislist.end(), [](const tuple<Coord, Coord, double>& a, const tuple<Coord, Coord, double>& b){
        return get<2>(a) < get<2>(b);
    });
    unordered_map<Coord, vector<Coord>> gr;
    for (const Coord& c : coords) {
        gr[c] = vector<Coord>();
    }
    size_t i = 0;
    int xa, xb;
    set<Coord> seen;
    while (i < dislist.size()) {
        Coord fr = get<0>(dislist[i]);
        Coord sc = get<1>(dislist[i]);
        gr[fr].push_back(sc);
        gr[sc].push_back(fr);
        seen.insert(fr);
        seen.insert(sc);
        i++;
        xa = fr.x;
        xb = sc.x;
        if (seen.size() == n) {
            if (completeMap(gr)) {
                break;
            }
        }
    }
    count *= xa;
    count *= xb;
    return count;
}

int main() {
    vector<string> strs = readfile();
    vector<Coord> coords_vec = coords(strs);
    long long c = part1(coords_vec);
    cout << c << endl;
    c = part2(coords_vec);
    cout << c << endl;
    return 0;
}