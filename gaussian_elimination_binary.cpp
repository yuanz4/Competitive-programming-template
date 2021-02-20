// m是行数，n是列数，不包括最后y的那一列，bieset是从右往左的
// sol有三种可能，0，1，无穷大
// where为-1处是independent的列，比如那一列都是0，
// 或是受制于别的变量比如x1+x3=0
// sol为0的情况是行太多了，在某一行中将已有的结果代入，满足不了
// 时间复杂度是O(n^3)

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 6;
const int INF = 2;

int gauss(vector<bitset<N>>& a, int m, int n, bitset<N>& ans) {
    vector<int> where(n, -1);
    for (int row = 0, col = 0; row < m && col < n; col++) {
        for (int i = row; i < m; i++) {
            if (a[i][col]) {
                swap(a[i], a[row]);
                break;
            }
        }
        if (!a[row][col])
            continue;
        where[col] = row;
        for (int i = 0; i < m; i++)
            if (i != row && a[i][col])
                a[i] ^= a[row];
        row++;
    }

    for (int i = 0; i < n; i++)
        if (where[i] != -1)
            ans[i] = a[where[i]][n] / a[where[i]][i];
    for (int i = 0; i < m; i++) {
        bool sum = 0;
        for (int j = 0; j < n; j++)
            sum ^= ans[j] * a[i][j];
        if (sum != a[i][n])
            return 0;
    }
    for (int i = 0; i < n; i++)
        if (where[i] == -1)
            return INF;
    return 1;
}

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);
    int m = 6, n = 5;
    vector<bitset<N>> a{
        bitset<N>("011101"),
        bitset<N>("111010"),
        bitset<N>("011101"),
        bitset<N>("111111"),
        bitset<N>("001111"),
        bitset<N>("001010")};
    bitset<N> ans;
    int sol = gauss(a, m, n, ans);
    for (auto& i: a)
        cout << i << '\n';
    cout << sol << '\n';
    cout << ans << '\n';
	return 0;
}