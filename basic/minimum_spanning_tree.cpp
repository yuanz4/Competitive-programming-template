// Prim's algorithm, implemented with set
// d[i] is the shortest distance to already selected nodes,
// so it is almost just one line difference from Dijkstra
// But we have to use visied here, or the node 1 will
// be popped twice. That is different from Dijkstra

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

int prim(vector<vector<pii>>& adj, int n) {
	int total = 0;
	vector<int> d(n, INT_MAX);
	d[0] = 0;
	set<pii> pq;
	pq.insert({0, 0});
	vector<int> visited(n, false);
	while (!pq.empty()) {
		auto it = pq.begin();
		int u = it->second;
		visited[u] = true;
		total += it->first;
		pq.erase(it);
		for (pii& edge: adj[u]) {
			int v = edge.first;
			int len = edge.second;
			if (!visited[v] && len < d[v]) {
				pq.erase({d[v], v});
				d[v] = len;
				pq.insert({d[v], v});
			}
		}
	}
	return total;
}

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n = 3;
	vector<vector<pii>> adj;
	adj.push_back({{1, 2}, {2, 3}});
	adj.push_back({{0, 2}, {2, 1}});
	adj.push_back({{0, 3}, {1, 1}});
	//   (0)
    // 2 / \ 3
    // (1)-(2)
    //    1
	int total = prim(adj, n);
	cout << total << '\n';
	return 0;
}