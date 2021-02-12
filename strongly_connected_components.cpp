// Kosaraju's algorithm, O(v+e)
// 每一个scc可以合并成一个缩合点，并且这些点之间是无环的
// 第一遍dfs1输出的是反向的拓扑排序，叶节点在反转图中会是root，
// 而root节点在反转图中会是叶节点，也就是不能通往外界，封闭，
// 将其删去，再找第二小的叶节点
// 最后会将scc们按拓扑排序的方法输出

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> g, gr;
vector<bool> used;
vector<int> order, component;

void dfs1(int u) {
    used[u] = true;
    for (auto& v: g[u]) {
        if (!used[v])
            dfs1(v);
    }
    order.push_back(u);
}

void dfs2(int u) {
    used[u] = true;
    component.push_back(u);
    for (auto& v: gr[u]) {
        if (!used[v])
            dfs2(v);
    }
}

int main() {
    int n = 4;
    g.resize(n);
    gr.resize(n);
    vector<pair<int, int>> edge{{0, 1}, {1, 2}, {2, 0}, {3, 0}};
    for (auto& i: edge) {
        int u = i.first;
        int v = i.second;
        g[u].push_back(v);
        gr[v].push_back(u);
    }

    used.assign(n, false);
    for (int i = 0; i < n; i++) {
        if (!used[i])
            dfs1(i);
    }
    used.assign(n, false);
    for (int i = 0; i < n; i++) {
        int v = order[n-1-i];
        if (!used[v]) {
            dfs2(v);
            for (auto& i: component)
                cout << i << ' ';
            cout << '\n';
            component.clear();
        }
    }
}