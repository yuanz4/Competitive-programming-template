// 可持久化segment tree可以记录历史更改，每次update都会
// 生成一条新的logn的链和新的root，
// 新的节点会指向未更改的child节点和发生更改的新的child节点
// 找区间内kth smallest。每个叶节点记录的是histogram，也就是每个元素
// 出现的频率：比如{0:1, 1:0, 2: 3, ..., n-1: 2}。然后每个节点记录
// 频率和，所以就和quick select一样，判断k是在左边还是右边
// 一开始每个叶节点都是0，然后我们每加入一个a[i]就生成一个新的root
// root_i记录a[1...i]的histogram prefix，所以如果要查询[l, r]区间，
// 每个节点就是root_r-root_{l-1}，要注意root_0是空的，root_1对应a_0
// 假如在非叶节点也记录了信息，那在update的时候，新的node要记录原node
// 里面的信息。这题里在constructor里面对sum进行了更新

#include <bits/stdc++.h>
using namespace std;

#define left(v) (v << 1)
#define right(v) ((v << 1) + 1)

struct Vertex {
    Vertex *l, *r;
    int sum;
    Vertex(int val) : l(NULL), r(NULL), sum(val) {}
    Vertex(Vertex *l, Vertex *r) : l(l), r(r), sum(0) {
        if (l) sum += l->sum;
        if (r) sum += r->sum;
    }
};

Vertex* build(int tl, int tr) {
    if (tl == tr)
        return new Vertex(0);
    int tm = (tl + tr) / 2;
    return new Vertex(build(tl, tm), build(tm+1, tr));
}

Vertex* update(Vertex* v, int tl, int tr, int pos) {
    if (tl == tr)
        return new Vertex(v->sum+1);
    int tm = (tl + tr) / 2;
    if (pos <= tm)
        return new Vertex(update(v->l, tl, tm, pos), v->r);
    return new Vertex(v->l, update(v->r, tm+1, tr, pos));
}

int find_kth(Vertex* vl, Vertex* vr, int tl, int tr, int k) {
    if (tl == tr)
        return tl;
    int tm = (tl + tr) / 2;
    int left_count = vr->l->sum - vl->l->sum;
    if (left_count >= k)
        return find_kth(vl->l, vr->l, tl, tm, k);
    return find_kth(vl->r, vr->r, tm+1, tr, k-left_count);
}

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n = 10;
    vector<int> a{2, 1, 5, 9, 7, 4, 0, 3, 8, 6};
	vector<Vertex*> roots;
	roots.push_back(build(0, n-1));
	for (int i = 0; i < n; i++)
	    roots.push_back(update(roots.back(), 0, n-1, a[i]));
	// find the 2th smallest number from the subarray [a[2], a[3], ..., a[9]]
	cout << find_kth(roots[2], roots[10], 0, n-1, 2) << '\n';
	return 0;
}