// priority queue usually pop last element
// default compare is less
// must define less compare

#include <bits/stdc++.h>
using namespace std;

struct NodeA {
	int x, y;
	NodeA(int x, int y) : x(x), y(y) {}
};

struct NodeB {
	int x, y;
	NodeB(int x, int y) : x(x), y(y) {}
};

bool operator<(const NodeB& a, const NodeB& b) {
	if (a.x == b.x)
		return a.y < b.y;
	return a.x < b.x;
};

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);

	auto cmp = [&](const NodeA& a, const NodeA& b) {
		if (a.x == b.x)
			return a.y < b.y;
		return a.x < b.x;
	};
	priority_queue<NodeA, vector<NodeA>, decltype(cmp)> pqa(cmp);
	pqa.emplace(3, 5);
	pqa.emplace(1, 3);
	pqa.emplace(6, 2);
	pqa.emplace(1, 1);
	while (!pqa.empty()) {
		NodeA cur = pqa.top();
		pqa.pop();
		cout << cur.x << " " << cur.y << '\n';
	}

	priority_queue<NodeB> pqb;
	pqb.emplace(3, 5);
	pqb.emplace(1, 3);
	pqb.emplace(6, 2);
	pqb.emplace(1, 1);
	while (!pqb.empty()) {
		NodeB cur = pqb.top();
		pqb.pop();
		cout << cur.x << " " << cur.y << '\n';
	}
	return 0;
}