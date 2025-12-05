#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>
#include <algorithm>

using namespace std;

vector<string> readfile() {
    ifstream filename("input05");
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

tuple<vector<tuple<long long, long long>>, vector<long long>> limits(vector<string>& rows) {
    tuple<vector<tuple<long long, long long>>, vector<long long>> lim;
    vector<tuple<long long, long long>> ranges;
    vector<long long> ids;
    for (const string& row : rows) {
        if (row.find('-') != string::npos) {
            tuple<long long, long long> range;
            size_t i = row.find('-');
            long long a = stoll(row.substr(0,i));
            long long b = stoll(row.substr(i+1));
            range = make_tuple(a, b);
            ranges.push_back(range);
        } else if (row.size() > 0) {
            long long id = stoll(row);
            ids.push_back(id);
        }
    }
    lim = make_tuple(ranges, ids);
    return lim;
}

long part1(tuple<vector<tuple<long long, long long>>, vector<long long>>& limits) {
    long count = 0;
    vector<tuple<long long, long long>> ranges = get<0>(limits);
    vector<long long> ids = get<1>(limits);
    for (const long long& id : ids) {
        for (const tuple<long long, long long>& range : ranges) {
            long long a = get<0>(range);
            long long b = get<1>(range);
            if (id >= a && id <= b) {
                count++;
                goto outer_continue;
            }
        }
        outer_continue:
            ;
    }
    return count;
}

long part2(tuple<vector<tuple<long long, long long>>, vector<long long>>& limits) {
    long sum = 0;
    vector<tuple<long long, long long>> ranges = get<0>(limits);
    vector<tuple<long long, long long>> fresh;
    for (const tuple<long long, long long>& range : ranges) {
        long long a = get<0>(range);
        long long b = get<1>(range);
        size_t fr = fresh.size();
        sort(fresh.begin(), fresh.end(), [](const tuple<long long, long long>& a, const tuple<long long, long long>& b) {
            if (get<0>(a) == get<0>(b)) {
                return get<1>(a) < get<1>(b);
            }
            return get<0>(a) < get<0>(b);
        });
        vector<int> deletes;
        for (size_t i = 0; i < fr; i++) {
            long long c = get<0>(fresh[i]);
            long long d = get<1>(fresh[i]);
            if (a > c && a <= d && b > d) {
                deletes.insert(deletes.begin(),i);
                a = c;
            } else if (a <= c && b >= d) {
                deletes.insert(deletes.begin(),i);
            } else if (a >= c && b <= d) {
                deletes.insert(deletes.begin(),i);
                a = c;
                b = d;
            } else if (a < c && b >= c && b < d) {
                deletes.insert(deletes.begin(),i);
                b = d;
            }
        }
        for (const int& i : deletes) {
            fresh.erase(fresh.begin() + i);
        }
        tuple<long long, long long> next = make_tuple(a, b);
        fresh.push_back(next);
    }
    for (const tuple<long long, long long>& f : fresh) {
        long long a = get<0>(f);
        long long b = get<1>(f);
        sum += b - a + 1;
    }
    return sum;
}

int main() {
    vector<string> strs = readfile();
    tuple<vector<tuple<long long, long long>>, vector<long long>> l = limits(strs);
    long c = part1(l);
    cout << c << endl;
    c = part2(l);
    cout << c << endl;
    return 0;
}