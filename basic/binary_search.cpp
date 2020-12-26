// 实现类似lower_bound，比较好的方法是将符合的结果存下来

#include <bits/stdc++.h>
using namespace std;

int binary(vector<int>& nums, int lower) {
	int n = nums.size();
	int ans = -1;
	int l = 0, r = n - 1;
	while (l <= r) {
		int mid = (l + r) / 2;
		if (nums[mid] >= lower) {
			ans = mid;
			r = mid - 1;
		} else
			l = mid + 1;
	}
	return ans;
}

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);
	vector<int> nums{1, 3, 5, 6, 8, 9};
	int lower = 6;
	cout << binary(nums, lower) << '\n';
	return 0;
}