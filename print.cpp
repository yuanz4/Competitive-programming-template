// if no any constructor in struct, it will use aggregate initialization

#include <bits/stdc++.h>
using namespace std;

struct Point {
    string name;
    int val;
    friend ostream& operator<<(ostream& os, const Point& p) {
        os << p.name << " " << p.val;
        return os;
    }
};

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
    os << '[';
    string sep;
    for (const auto& x: v)
        os << sep << x, sep = ", ";
    return os << ']';
}

template<typename A, typename B>
ostream& operator<<(ostream& os, const pair<A, B>& p) {
    return os << '(' << p.first << ", " << p.second << ')';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    vector<int> v{1, 2, 4, 2, 1};
    cout << v << '\n';
    unordered_map<int, int> m{{1, 22}, {343, 255}, {23, 344}};
    for (auto& i: m)
        cout << i << '\n';
    Point p = {"dsfd", 2};
    cout << p << '\n';
    return 0;
}