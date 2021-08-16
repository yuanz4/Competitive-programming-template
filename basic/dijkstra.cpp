// 是一种贪心算法，在pq中可能有很多到v的路径，不一定是所有的
// （可能有很远的到v的路径还没被包括），不过一定包括最优的，
// 因此一个点第一次被pop出来就是最优解。d[v]会被更新多次。
// 有至少四种写法：
// 1. 只用d，因为在push的时候更新了d，所以只有当du==d也就是最短
// 的时候（也是第一次pop v）才会被考虑
// 2. 用visited来记录第一次pop的v，要注意在push的时候不用
// 判断!visited[v]。是方法一的累赘版
// 3. 前两种都是lazy delete，pq的size可能会比O(V)要大。在这里我们
// 直接找到v对应的pair然后替换。一种优化方法是不存pair，只存v的index，
// 然后overload set的comparator
// 4. 最快的是用heap实现decrease_key（更快的可以用Fibonacci）
// 既有set的优点（replace old value，保持size不会超过V）
// ，也有priority_queue的优点（只更新最小值，别的部分不用sorted）。同样的
// 时间复杂度，但是更快

// 时间复杂度：O((V+E)logV)。这是基于第三种方法的，pq最大为O(V),
// pop需要VlogV，push需要ElogV
// 只适用于所有边都为非负的情况，这样全局最小值不可能再被更新
// 在Dense的图上（E=V^2）会比iteration的做法O(V^2+E)慢
// 用Fibonacci heap可以达到O(VlogV+E)

// 假如是A*，f(v) = g(v) + h(v)，g是已走路程，h是预计剩余路程
// 1. admissible: g(v) <= actual remaining cost, guarantee optimal, 
// better heuristic faster
// 2. consistent: h(x) <= d(x, y) + h(y), every node popped once,
// guarantee efficiency
// 可以将dijkstra中的d[n]改为g[n]，pq改为f方便理解，另外需要一个h()。
// 初始化时f[0] = h(0)，然后每次push进去的是f = g + h，push前比较和
// 更新仍然用的是g，遇到target时会终止

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

vector<int> dijkstra_d(vector<vector<pii>>& adj, int n) {
	vector<int> d(n, INT_MAX);
	d[0] = 0;
	priority_queue<pii, vector<pii>, greater<pii>> pq;
	pq.push({0, 0});
	while (!pq.empty()) {
		int u = pq.top().second;
		int du = pq.top().first;
		pq.pop();
		if (du != d[u])
			continue;
		for (pii& edge: adj[u]) {
			int v = edge.first;
			int w = edge.second;
			if (w + d[u] < d[v]) {
				d[v] = w + d[u];
				pq.push({d[v], v});
			}
		}
	}
	return d;
}

vector<int> dijkstra_visited(vector<vector<pii>>& adj, int n) {
	vector<int> d(n, INT_MAX);
	d[0] = 0;
	bool visited[n] = {};
	priority_queue<pii, vector<pii>, greater<pii>> pq;
	pq.push({0, 0});
	while (!pq.empty()) {
		int u = pq.top().second;
		pq.pop();
		if (visited[u])
			continue;
		visited[u] = true;
		for (pii& edge: adj[u]) {
			int v = edge.first;
			int w = edge.second;
			if (w + d[u] < d[v]) {
				d[v] = w + d[u];
				pq.push({d[v], v});
			}
		}
	}
	return d;
}

vector<int> dijkstra_set(vector<vector<pii>>& adj, int n) {
	vector<int> d(n, INT_MAX);
	d[0] = 0;
	set<pii> pq;
	pq.insert({0, 0});
	while (!pq.empty()) {
		auto it = pq.begin();
		int u = it->second;
		pq.erase(it);
		for (pii& edge: adj[u]) {
			int v = edge.first;
			int w = edge.second;
			if (w + d[u] < d[v]) {
				pq.erase({d[v], v});
				d[v] = w + d[u];
				pq.insert({d[v], v});
			}
		}
	}
	return d;
}

vector<int> dijkstra_heap(vector<vector<pii>>& adj, int n) {
	vector<int> d(n, INT_MAX);
	vector<int> heap(n + 2);
	vector<int> heapIdx(n, 0);
	int tail = 1;

	auto heapDown = [&](int x) {
		while (x * 2 <= tail) {
			int y = x * 2;
			if (y < tail && d[heap[y]] > d[heap[y+1]])
				y++;
			if (d[heap[x]] > d[heap[y]]) {
				swap(heap[x], heap[y]);
				heapIdx[heap[x]] = x;
				heapIdx[heap[y]] = y;
				x = y;
			} else
				break;
		}
	};

	auto heapUp = [&](int x) {
		while (x > 1) {
			int y = x / 2;
			if (d[heap[x]] < d[heap[y]]) {
				swap(heap[x], heap[y]);
				heapIdx[heap[x]] = x;
				heapIdx[heap[y]] = y;
				x = y;
			} else
				break;
		}
	};

	heap[tail] = 0;
	heapIdx[0] = 1;
	d[0] = 0;
	while (tail > 0) {
		int u = heap[1];
		heap[1] = heap[tail];
		tail--;
		heapDown(1);
		for (pii& edge: adj[u]) {
			int v = edge.first;
			int w = edge.second;
			if (d[u] + w < d[v])	{
				d[v] = d[u] + w;
				if (heapIdx[v] == 0)
					heapIdx[v] = ++tail;
				heap[heapIdx[v]] = v;
				heapUp(heapIdx[v]);
				heapDown(heapIdx[v]);
			}
		}
	}
	return d;
}

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n = 5;
	vector<vector<pii>> adj;
	adj.push_back({{1, 2}, {2, 1}, {4, 5}});
	adj.push_back({{0, 2}, {3, 1}});
	adj.push_back({{0, 1}, {3, 3}});
	adj.push_back({{1, 1}, {2, 3}, {4, 5}});
	adj.push_back({{0, 5}, {3, 5}});
	//   (0)-------
    // 2 / \ 1    | 5
    // (1) (2)   (4)
    // 1 \ / 3    | 5
    //   (3)-------
	vector<int> d = dijkstra_heap(adj, n);
	cout << d[3] << '\n';
	return 0;
}