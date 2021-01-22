// 用lambda表达式可以捕获外部变量，不用将变量写成global
// []默认不捕获外部变量，[&]以引用，[=]以值捕获，一般写成[&]
// 一般来说可以直接写成auto，但是如果内部也要call这个function的话
// 就得写成function，<>内部是和输入输出完全一致的变量类型
// 可以explicitly定义return type，这时候会将类型进行强制转换
// 假如不定义，那么多个返回的类型必须一致，不然会报错

#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);
	function<void(int, vector<int>&)> dfs = [&](int i, vector<int>& sequence) {
		if (i < 0)
			return;
		sequence.push_back(i);
		dfs(i-1, sequence);
	};
	vector<int> sequence;
	dfs(2, sequence);
	for (auto& i: sequence)
		cout << i << ' ';
	cout << '\n';

	int a = 123;
    auto f = [&] {
    	cout << a << endl;
    };
    a = 321;
    f(); // 321

    a = 123;
    auto g = [=] {
    	cout << a << endl;
    };
    a = 321;
    g(); // 123

    vector<int> v{3, 1, 2};
    auto cmp = [](int& a, int& b) -> bool {
    	if (a < b)
    		return 0.0;
    	return 1;
    };
    sort(v.begin(), v.end(), cmp);
    for (auto& i: v)
    	cout << i << ' ';
    cout << '\n';
	return 0;
}