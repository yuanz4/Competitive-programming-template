// 也可以用来检测环，但是只有当每条边最多只有一条出边时有用
// 比如这个就是反例，会有两个点的p一样，但是没有环
//    d--- 
//    ^  |
//    |  v
// a->b->c
// 单独使用路径压缩和按秩合并，都是O(logn)，
// 一起使用时可以降低到alpha(n)，十分小，近似为一个常数
// 按秩合并时，秩是树的深度或大小，小的树作为大的树的子树
// 这里使用的是深度

#include <bits/stdc++.h>
using namespace std;

vector<int> p, size;

void build(int n) {
	p.resize(n);
	size.resize(n);
	for (int i = 0; i < n; i++) {
		p[i] = i;
		size[i] = 0;
	}
}

int get(int x) {
	if (x == p[x])
		return x;
	return p[x] = get(p[x]);
}

void merge(int x, int y) {
	x = get(x);
	y = get(y);
	if (size[x] < size[y])
		p[x] = y;
	else if (size[x] > size[y])
		p[y] = x;
	else {
		p[y] = x;
		size[x] += 1;
	}
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