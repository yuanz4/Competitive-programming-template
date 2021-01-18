// lazy propogation可以对一段范围进行更新
// 在这里是assign一个值到区间，然后对某点进行查询
// update时先push再update，最后每个小segment要和区间完全重合，
// 因此当前区间所有值都有lazy标记，整个subtree也都是这个值
// 所以向下push会完全覆盖子区间，即使子区间有lazy标记也没关系，直接覆盖
// 在update的时候划分了目标区域，min和max的使用覆盖了所有情况
// 还有很多变形，比如加某个值到区间，然后查询单点或是查询区间

#include <bits/stdc++.h>
using namespace std;

#define left(v) (v << 1)
#define right(v) ((v << 1) + 1)
const int MAX = 5007;
int n;
int a[MAX];
int t[4*MAX];
bool marked[4*MAX];

void build(int v, int tl, int tr) {
	if (tl == tr)
		t[v] = a[tl];
	else {
		int tm = (tl + tr) / 2;
		build(left(v), tl, tm);
		build(right(v), tm+1, tr);
		t[v] = 0;
	}
}

void push(int v) {
    if (marked[v]) {
        t[left(v)] = t[right(v)] = t[v];
        marked[left(v)] = marked[right(v)] = true;
        marked[v] = false;
    }
}

void update(int v, int tl, int tr, int l, int r, int new_val) {
    if (l > r) 
        return;
    if (l == tl && tr == r) {
        t[v] = new_val;
        marked[v] = true;
    } else {
        push(v);
        int tm = (tl + tr) / 2;
        update(left(v), tl, tm, l, min(tm, r), new_val);
        update(right(v), tm+1, tr, max(l, tm+1), r, new_val);
    }
}

void UPDATE(int l, int r, int new_val) {
    update(1, 0, n-1, l, r, new_val);
}

int get(int v, int tl, int tr, int pos) {
    if (tl == tr)
        return t[v];
    push(v);
    int tm = (tl + tr) / 2;
    if (pos <= tm) 
        return get(left(v), tl, tm, pos);
    return get(right(v), tm+1, tr, pos);
}

int GET(int pos) {
	return get(1, 0, n-1, pos);
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
	UPDATE(0, 2, 10);
	cout << GET(2) << '\n';;
	UPDATE(2, 3, 20);
	cout << GET(2) << '\n';
	cout << GET(3) << '\n';
	return 0;
}