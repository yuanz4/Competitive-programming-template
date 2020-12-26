// topological sort without cycle detection using dfs

#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> adj;
vector<bool> visited;
vector<int> ans;

void dfs(int u) {
    visited[u] = true;
    for (int v: adj[u]) {
        if (!visited[v])
            dfs(v);
    }
    ans.push_back(u);
}

void topological_sort() {
    visited.resize(n);
    for (int i = 0; i < n; i++) {
        if (!visited[i])
            dfs(i);
    }
    reverse(ans.begin(), ans.end());
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    n = 3;
    adj.resize(n);
    adj[0].push_back(2);
    adj[1].push_back(2);
    topological_sort();
    for (int i: ans)
        cout << i << " ";
    cout << '\n';
    return 0;
}