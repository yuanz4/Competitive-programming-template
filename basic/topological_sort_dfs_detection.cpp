// topological sort with cycle detection using dfs
// 0: not visited
// 1: visited in this dfs
// 2: visited in previous dfs

#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> adj;
vector<int> color;
vector<int> ans;

void dfs(int u) {
    if (color[u] == 2)
        return;
    if (color[u] == 1) {
        cout << "Not DAG!" << '\n';
        return;
    }
    color[u] = 1;
    for (int v: adj[u])
        dfs(v);
    color[u] = 2;
    ans.push_back(u);
}

void topological_sort() {
    color.resize(n);
    for (int i = 0; i < n; i++)
        dfs(i);
    reverse(ans.begin(), ans.end());
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    n = 3;
    adj.resize(n);
    adj[0].push_back(2);
    adj[2].push_back(1);
    adj[1].push_back(0);
    topological_sort();
    for (int i: ans)
        cout << i << " ";
    cout << '\n';
    return 0;
}