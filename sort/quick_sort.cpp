#include <bits/stdc++.h>
using namespace std;

int _partition(vector<int>& nums, int l, int r) {
    int x = nums[r];
    for (int j = l; j < r; j++) {
        if (nums[j] <= x)
            swap(nums[l++], nums[j]);
    }
    swap(nums[l], nums[r]);
    return l;
}

void _quick_sort(vector<int>& nums, int l, int r) {
	if (l < r) {
		int p = _partition(nums, l, r);
		_quick_sort(nums, l, p-1);
		_quick_sort(nums, p+1, r);
	}
}

void quick_sort(vector<int>& nums) {
	_quick_sort(nums, 0, nums.size()-1);
}

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);
	vector<int> v{3, 1, 2, 3, 4, 6, 1, 3, 4, 2, 5, 6, 2, 3};
	quick_sort(v);
	for (int i: v)
		cout << i << ' ';
	cout << '\n';
	return 0;
}