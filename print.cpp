// if no any constructor in struct, it will use aggregate initialization
// if total n arguments, and in constructor m (<= n) is given,
// will initialize first m arguments
// structured binding in c++ 17: auto[x, y] = ...
// #x means stringizing, convert macro parameters to string literals
// ... and __VA_ARGS__ are variadic functions
// 注意将print给output到cout而不是cerr，不然假如还有别的输出的话顺序会不对
// 在output double时用fixed来控制小数点后的精度

#include <bits/stdc++.h>
using namespace std;

typedef tuple<int, double, string> ti;

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

// -------------------------------------------------------------------------

#define DEBUG

void debug_out() {cout << endl;}

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {cout << " " << H, debug_out(T...);}

#ifdef DEBUG
#define print(...) cout << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define print(...)
#endif

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

    vector<pair<int, string>> vec{{1, "12313"}, {23, "sdfdf"}};
    for (auto& [i, s]: vec)
        cout << i << " " << s << '\n';

    ti tu{1, 2.0, "sssa"};
    auto [x, y, z] = tu;
    cout << x << " " << y << " " << z << '\n';

    string s = "vsoiwkm";
    int l = 213;
    double d = 23.34;
    print(s, l, d);

    double dou = 23.123148901330;
    cout.precision(9);
    cout << fixed << dou << '\n';
    return 0;
}