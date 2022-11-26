// priority queue usually pop last element
// default compare is less

#include <bits/stdc++.h>
using namespace std;

struct Node {
	int x, y;
	Node(int x, int y) : x(x), y(y) {}
};

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);
	auto cmp = [&](const Node& a, const Node& b) {
		if (a.x == b.x)
			return a.y < b.y;
		return a.x < b.x;
	};
	priority_queue<Node, vector<Node>, decltype(cmp)> pq(cmp);
	pq.emplace(3, 5);
	pq.emplace(1, 3);
	pq.emplace(6, 2);
	pq.emplace(1, 1);
	while (!pq.empty()) {
		Node cur = pq.top();
		pq.pop();
		cout << cur.x << " " << cur.y << '\n';
	}
	return 0;
}