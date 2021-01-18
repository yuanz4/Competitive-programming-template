// tl和tr指的是当前segment的boundary，与a的index相符
// 这里是区间sum查询，并且update单个元素
// lazy propogation可以对一段范围进行更新，一般用于sum

#include <bits/stdc++.h>
using namespace std;

#define left(v) (v << 1)
#define right(v) ((v << 1) + 1)
const int MAX = 5007;
int n;
int a[MAX];
int t[4*MAX];

void build(int v, int tl, int tr) {
	if (tl == tr)
		t[v] = a[tl];
	else {
		int tm = (tl + tr) / 2;
		build(left(v), tl, tm);
		build(right(v), tm+1, tr);
		t[v] = t[left(v)] + t[right(v)];
	}
}

int sum(int v, int tl, int tr, int l, int r) {
	if (l > r)
		return 0;
	if  (l == tl && r == tr)
		return t[v];
	int tm = (tl + tr) / 2;
	return sum(left(v), tl, tm, l, min(tm, r))
		+ sum(right(v), tm+1, tr, max(l, tm+1), r);
}

void update(int v, int tl, int tr, int pos, int new_val) {
	if (tl == tr)
		t[v] = new_val;
	else {
		int tm = (tl + tr) / 2;
		if (pos <= tm)
			update(left(v), tl, tm, pos, new_val);
		else
			update(right(v), tm+1, tr, pos, new_val);
		t[v] = t[left(v)] + t[right(v)];
	}
}

int SUM(int l, int r) {
	return sum(1, 0, n-1, l, r);
}

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);
    n = 5;
    a[0] = 1;
    a[1] = 3;
    a[2] = -2;
    a[3] = 8;
    a[4] = -7;
	build(1, 0, n-1);
	cout << SUM(2, 4) << '\n';
	return 0;
}