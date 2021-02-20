// topological sort with cycle detection using Kahn
// 假如有环，则在环中的点和从环出去的点都不会在ans中

#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> adj;
vector<int> ans;

void topological_sort() {
    vector<int> in_degree(n, 0);
    for (int u = 0; u < n; u++) {
        for (int v: adj[u])
            in_degree[v]++;
    }
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (in_degree[i] == 0)
            q.push(i);
    }
    int cnt = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ans.push_back(u);
        for (int v: adj[u]) {
            if (--in_degree[v] == 0)
                q.push(v);
        }
        cnt++;
    }
    if (cnt != n)
        cout << "Not DAG!" << '\n';
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