// 链式前向星，边是带编号的，可以将边成对存，适用于网络流，每次用之前要清空head
// the i in update() is actually the index of edge which directs to x
// Ford–Fulkerson未定义增广路的寻找方法，O(E*|f|)
// Edmonds-Karp，用bfs寻找任意一条增广路，则是shortest path，O(VE^2)

#include <bits/stdc++.h>
using namespace std;

const int inf = INT_MAX, N = 10, M = 20;
int head[N], ver[M], edge[M], Next[M];
int v[N], incf[N], pre[N];
int s, t, tot, maxflow;

void add(int x, int y, int z) {
	ver[++tot] = y, edge[tot] = z, Next[tot] = head[x], head[x] = tot;
	ver[++tot] = x, edge[tot] = 0, Next[tot] = head[y], head[y] = tot;
}

bool bfs() {
	memset(v, 0, sizeof(v));
	queue<int> q;
	q.push(s);
	v[s] = 1;
	incf[s] = inf;
	while (q.size()) {
		int x = q.front();
		q.pop();
		for (int i = head[x]; i; i = Next[i]) {
			if (edge[i]) {
				int y = ver[i];
				if (v[y])
					continue;
				incf[y] = min(incf[x], edge[i]);
				pre[y] = i;
				q.push(y);
				v[y] = 1;
				if (y == t)
					return true;
			}
		}
	}
	return false;
}

void update() {
	int x = t;
	while (x != s) {
		int i = pre[x];
		edge[i] -= incf[t];
		edge[i^1] += incf[t];
		x = ver[i^1];
	}
	maxflow += incf[t];
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
    while (bfs())
    	update();
	cout << maxflow << '\n';
	return 0;
}