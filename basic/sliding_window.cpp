// 这里的题目是Minimum Size Subarray Sum，有固定i和固定j两种写法
// 精髓：对于每个i找到最tight的右边界f(i)，f是单调非递减的

#include <bits/stdc++.h>
using namespace std;

int forward(vector<int>& nums, int s) {
    int i = 0, j = 0;
    int n = nums.size();
    int total = 0, ret = INT_MAX;
    while (i < n) {
        while (j < n && total < s)
            total += nums[j++];
        if (total < s)
            break;
        ret = min(ret, j - i);
        total -= nums[i++];
    }
    return ret == INT_MAX ? 0 : ret;
}

int backward(vector<int>& nums, int s) {
    int i = 0, j = 0;
    int total = 0, ret = INT_MAX;
    while (j < nums.size()) {
        total += nums[j++];
        while (total >= s) {
            ret = min(ret, j - i);
            total -= nums[i++];
        }
    }
    return ret == INT_MAX ? 0 : ret;
}

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);
	vector<int> nums{2,3,1,2,4,3};
	int s = 7;
	cout << forward(nums, s) << '\n';
	cout << backward(nums, s) << '\n';
	return 0;
}