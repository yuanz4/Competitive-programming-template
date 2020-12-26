// 也可以用来检测环，但是只有当每条边最多只有一条出边时有用
// 比如这个就是反例，会有两个点的p一样，但是没有环
//    d--- 
//    ^  |
//    |  v
// a->b->c

#include <bits/stdc++.h>
using namespace std;

vector<int> p;

void build(int n) {
	p.resize(n);
	for (int i = 0; i < n; i++)
		p[i] = i;
}

int get(int x) {
	if (x == p[x])
		return x;
	return p[x] = get(p[x]);
}

void merge(int x, int y) {
	p[get(y)] = get(x);
}

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);
	int n = 4;
	build(n);
	merge(1, 3);
	merge(2, 1);
	for (int i = 0; i < n; i++)
		cout << get(i) << '\n';
	return 0;
}