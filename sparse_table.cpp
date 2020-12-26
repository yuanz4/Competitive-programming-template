// 用来找range minimum或是maximum，精髓是一个元素可重复贡献，所以在
// get时两个range overlap也没关系
// 32-__builtin_clz(n)-1 == log2(n)
// sparse table的范围要取到max_log使得2^max_log >= n，因此不用-1

#include <bits/stdc++.h>
using namespace std;

struct SparseTable {
	int n;
	vector<vector<int>> mat;

	SparseTable(vector<int>& v) {
		n = v.size();
		int max_log = 32 - __builtin_clz(n);
		mat.resize(max_log);
		mat[0] = v;
		for (int j = 1; j < max_log; j++) {
			mat[j].resize(n - (1 << j) + 1);
			for (int i = 0; i <= n - (1 << j); i++)
				mat[j][i] = min(mat[j-1][i], mat[j-1][i+(1<<(j-1))]);
		}
	}

	int get(int from, int to) {
		int lg = 32 - __builtin_clz(to - from + 1) - 1;
		return min(mat[lg][from], mat[lg][to-(1<<lg)+1]);
	}
};


int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);
	vector<int> v{1, 3, 2, 4, 5, 2};
	SparseTable st(v);
	cout << st.get(0, 1) << '\n';
	cout << st.get(3, 4) << '\n';
	cout << st.get(1, 4) << '\n';
	return 0;
}