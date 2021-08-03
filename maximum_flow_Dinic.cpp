// 是EK的加强版，可以处理更大图
// d代表节点的层次，即到s的最短距离，是DAG
// 先用bfs构建layered network，然后用dfs找blocking flow
// blocking flow contains at least an edge which is saturated by this flow
// 并要去掉无法被push flow的edge作为剪枝
// 可以证明找blocking flow会用O(VE)的时间，与EK的证明相同
// 另外可以证明最多有O(V)次iteration，所以O(V^2E)

#include <bits/stdc++.h>
using namespace std;

const int inf = INT_MAX, N = 10, M = 20;
int head[N], ver[M], edge[M], Next[M], d[N];
int n, m, s, t, tot, maxflow;

void add(int x, int y, int z) {
	ver[++tot] = y, edge[tot] = z, Next[tot] = head[x], head[x] = tot;
	ver[++tot] = x, edge[tot] = 0, Next[tot] = head[y], head[y] = tot;
}

bool bfs() {
	memset(d, 0, sizeof(d));
	queue<int> q;
	q.push(s);
	d[s] = 1;
	while (q.size()) {
		int x = q.front();
		q.pop();
		for (int i = head[x]; i; i = Next[i]) {
			if (edge[i] && !d[ver[i]]) {
				q.push(ver[i]);
				d[ver[i]] = d[x] + 1;
				if (ver[i] == t)
					return true;
			}
		}
	}
	return false;
}

int dinic(int x, int flow) {
	if (x == t)
		return flow;
	int rest = flow;
	for (int i = head[x]; i && rest; i = Next[i]) {
		if (edge[i] && d[ver[i]] == d[x] + 1) {
			int k = dinic(ver[i], min(rest, edge[i]));
			if (!k)
				d[ver[i]] = 0;
			edge[i] -= k;
			edge[i^1] += k;
			rest -= k;
		}
	}
	return flow - rest;
}

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n = 4, m = 5;
    s = 0;
    t = 3;
    tot = 1;
    maxflow = 0;
    memset(head, 0, sizeof(head));

    //   0
    //  / \
    // 1 - 2
    //  \ /
    //   3
    add(0, 1, 10);
    add(0, 2, 5);
    add(1, 2, 5);
    add(1, 3, 5);
    add(2, 3, 10);

    int flow = 0;
    while (bfs()) {
    	while (flow = dinic(s, inf))
    		maxflow += flow;
    }
	cout << maxflow << '\n';
	return 0;
}