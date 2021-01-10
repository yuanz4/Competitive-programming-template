// 这里的题目是，对于每个index找到下一个比他大的值的index的距离
// 单调栈只存取那些未来可能有用的值，舍弃一定不会被用到的

#include <bits/stdc++.h>
using namespace std;

vector<int> nextGreater(vector<int>& v) {
	stack<int> s;
    int n = v.size();
    vector<int> ans(n);
    for (int i = n - 1; i >= 0; i--) {
        while (s.size() && v[i] >= v[s.top()])
            s.pop();
        if (s.empty())
            ans[i] = 0;
        else
            ans[i] = s.top() - i;
        s.push(i);
    }
    return ans;
}

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);
	vector<int> v{73, 74, 75, 71, 69, 72, 76, 73};
	vector<int> ans = nextGreater(v);
	for (auto& i: ans)
		cout << i << ' ';
	cout << '\n';
	return 0;
}