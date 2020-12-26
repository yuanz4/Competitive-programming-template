// pii in parent means <leader index, parity of path up to its leader>

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

vector<pii> parent;
vector<int> depth;
vector<int> bipartite;

void build(int n) {
	parent.resize(n);
	depth.resize(n);
	bipartite.assign(n, 1);
	for (int i = 0; i < n; i++)
		parent[i] = {i, 0};
}

void make_set(int v) {
    parent[v] = {v, 0};
    depth[v] = 0;
    bipartite[v] = 1;
}

pii find_set(int v) {
    if (v != parent[v].first) {
        int parity = parent[v].second;
        parent[v] = find_set(parent[v].first);
        parent[v].second ^= parity;
    }
    return parent[v];
}

void add_edge(int a, int b) {
    pii pa = find_set(a);
    a = pa.first;
    int x = pa.second;

    pii pb = find_set(b);
    b = pb.first;
    int y = pb.second;

    if (a == b) {
        if (x == y)
            bipartite[a] = false;
    } else {
        if (depth[a] < depth[b])
            swap(a, b);
        parent[b] = {a, x^y^1};
        bipartite[a] &= bipartite[b];
        if (depth[a] == depth[b])
            depth[a]++;
    }
}

bool is_bipartite(int v) {
    return bipartite[find_set(v).first];
}

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);
	int n = 5;
	build(n);
	// 0 - 1
	//  \2/
	add_edge(0, 1);
	cout << is_bipartite(0) << '\n';
	add_edge(1, 2);
	cout << is_bipartite(1) << '\n';
	add_edge(0, 2);
	cout << is_bipartite(0) << '\n';
	cout << is_bipartite(1) << '\n';
	cout << is_bipartite(2) << '\n';
	// 0 - 1 - 3 - 4
	//  \2/
	add_edge(3, 4);
	cout << is_bipartite(3) << '\n';
	add_edge(1, 3);
	cout << is_bipartite(3) << '\n';
	return 0;
}