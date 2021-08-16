// 又叫Binary Indexed Tree，记录prefix sum
// 支持单点更新，要注意index是从1开始的，x&-x表示最后一个1
// 对于ask要累加所有之前的线段，比如说7包含1-4(100)，5-6(110)，7(111)
// 对于add要更新所有包含它的线段，比如说5被记录在5(101)，6(110)，8(1000)
// 经常会配合离散化(coordinate compression)，即重新编号，(90, -39, 23) -> (3, 1, 2)

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 2e5+7;
int t[MAXN];

int ask(int x) {
    int ans = 0;
    for (; x; x -= x&-x)
    	ans += t[x];
    return ans;
}

void add(int x, int y) {
    for(; x < MAXN; x += x&-x)
        t[x] += y;
}

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);
    // query the frequency prefix sum
	vector<int> v{2, 4, 5, 5, 6, 6, 6, 7, 7, 8, 9};
	for (auto& i: v)
		add(i, 1);
	cout << ask(6) << '\n';
	cout << ask(9) << '\n';
	return 0;
}