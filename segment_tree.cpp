// lazy propogation可以对一段范围进行更新，一般用于sum

#include <bits/stdc++.h>
using namespace std;

const int MAX = 5007;
int n;
int a[MAX];
int st[4*MAX];

int left(int p) {
	return p << 1;
}

int right(int p) {
	return (p << 1) + 1;
}

void build(int p, int L, int R) {
	if (L == R)
		st[p] = L;
	else {
		build(left(p), L, (L+R)/2);
		build(right(p), (L+R)/2+1, R);
		int p1 = st[left(p)], p2 = st[right(p)];
		st[p] = (a[p1] <= a[p2]) ? p1 : p2;
	}
}

int rmq(int p, int L, int R, int i, int j) {
	if (i > R || j < L)
		return -1;
	if (L >= i && R <= j)
		return st[p];
	int p1 = rmq(left(p), L, (L+R)/2, i, j);
	int p2 = rmq(right(p), (L+R)/2+1, R, i, j);
	if (p1 == -1)
		return p2;
	if (p2 == -1)
		return p1;
	return (a[p1] <= a[p2]) ? p1 : p2;
}

int RMQ(int i, int j) {
	return rmq(1, 0, n-1, i, j);
}

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	build(1, 0, n-1);
	int l, r;
	RMQ(l, r);
	return 0;
}