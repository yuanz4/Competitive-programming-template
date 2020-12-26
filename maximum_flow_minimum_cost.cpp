// 链式前向星，边是带编号的，可以将边成对存，适用于网络流，每次用之前要清空head
// the i in update() is actually the index of edge which directs to x
// 用SPFA寻找一条单位费用之和最小的增广路
// if want maximum flow maximum cost, change:
// memset(d, 0xcf, sizeof(d));
// if (d[y] < d[x] + cost[i])
// if (d[t] == 0xcfcfcfcf)


#include <bits/stdc++.h>
using namespace std;

const int inf = 0x3f3f3f3f, N = 20, M = 40;
int head[N], ver[M], edge[M], Next[M], cost[M];
int v[N], incf[N], pre[N], d[N];
int s, t, tot, maxflow, ans;

void add(int x, int y, int z, int c) {
	ver[++tot] = y, edge[tot] = z, cost[tot] = c, Next[tot] = head[x], head[x] = tot;
	ver[++tot] = x, edge[tot] = 0, cost[tot] = -c, Next[tot] = head[y], head[y] = tot;
}

bool spfa() {
	memset(v, 0, sizeof(v));
	memset(d, 0x3f, sizeof(d));
	queue<int> q;
	q.push(s);
	d[s] = 0;
	v[s] = 1;
	incf[s] = inf;
	while (q.size()) {
		int x = q.front();
		q.pop();
		v[x] = 0;
		for (int i = head[x]; i; i = Next[i]) {
			if (edge[i]) {
				int y = ver[i];
				if (d[y] > d[x] + cost[i]) {
					d[y] = d[x] + cost[i];
					incf[y] = min(incf[x], edge[i]);
					pre[y] = i;
					if (!v[y]) {
						v[y] = 1;
						q.push(y);
					}
				}
			}
		}
	}
	if (d[t] == inf)
		return false;
	return true;
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
	ans += d[t] * incf[t];
}

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);
    s = 0, t = 7;
    tot = 1;
    maxflow = 0;
    ans = 0;
    memset(head, 0, sizeof(head));

	//  /1-4\
    // 0-2-5-7
    //  \3-6/
    add(0, 1, 1, 0);
    add(0, 2, 1, 0);
    add(0, 3, 1, 0);
    add(1, 4, 1, 5);
    add(2, 5, 1, 3);
    add(3, 6, 1, 1);
    add(4, 7, 1, 0);
    add(5, 7, 1, 0);
    add(6, 7, 1, 0);
    while (spfa())
    	update();
    cout << maxflow << '\n';
	cout << ans << '\n';
	return 0;
}