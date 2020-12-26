// 这里的题目是Sliding Window Maximum
// 单调队列用来找range min和range max
// 在尾部pop时用>=和>都行无所谓

#include <bits/stdc++.h>
using namespace std;

vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> d;
    vector<int> ans;
    for (int i = 0; i < nums.size(); i++) {
        if (i-d.front() >= k)
            d.pop_front();
        while (!d.empty() && nums[i] >= nums[d.back()])
            d.pop_back();
        d.push_back(i);
        if (i >= k-1)
            ans.push_back(nums[d.front()]);
    }
    return ans;
}

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);
	vector<int> nums{1,3,-1,-3,5,3,6,7};
	int k = 3;
	vector<int> ans = maxSlidingWindow(nums, k);
	for (auto& i: ans)
		cout << i << ' ';
	cout << '\n';
	return 0;
}