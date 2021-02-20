// 假如要计算对某一个p的modular，那需要将double改为int，
// 并且将加减乘除都改为模运算

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const double EPS = 1e-9;
const int INF = 2;

int gauss(vector<vector<double>>& a, vector<double>& ans) {
    int n = a.size();
    int m = a[0].size() - 1;
    vector<int> where(n, -1);
    for (int row = 0, col = 0; row < m && col < n; col++) {
        int sel = row;
        for (int i = row; i < m; i++)
            if (abs(a[i][col]) > abs(a[sel][col]))
                sel = i;
        if (abs(a[sel][col]) < EPS)
            continue;
        for (int i = col; i <= n; i++)
            swap(a[sel][i], a[row][i]);
        where[col] = row;
        for (int i = 0; i < m; i++)
            if (i != row) {
                double c = a[i][col] / a[row][col];
                for (int j = col; j <= n; ++j)
                    a[i][j] -= a[row][j] * c;
            }
        ++row;
    }

    ans.assign(m, 0);
    for (int i = 0; i < n; i++)
        if (where[i] != -1)
            ans[i] = a[where[i]][n] / a[where[i]][i];
    for (int i = 0; i < m; i++) {
        double sum = 0;
        for (int j = 0; j < n; j++)
            sum += ans[j] * a[i][j];
        if (abs(sum - a[i][n]) > EPS)
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
    vector<vector<double>> a{
        {1, 1, 1, 1, 10},
        {2, 3, 1, 1, 15},
        {3, -1, 2, -1, 3},
        {4, 1, -3, 2, 5}};
    vector<double> ans;
    int sol = gauss(a, ans);
    for (auto& i: a) {
        for (auto& j: i)
            cout << j << ' ';
        cout << '\n';
    }
    cout << sol << '\n';
    for (auto& i: ans)
        cout << i << ' ';
    cout << '\n';
	return 0;
}