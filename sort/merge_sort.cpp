#include <bits/stdc++.h>
using namespace std;

void _merge(vector<int>& v, int l, int mid, int r) {
	vector<int> left(v.begin()+l, v.begin()+mid+1);
	vector<int> right(v.begin()+mid+1, v.begin()+r+1);
	int i = 0, j = 0;
    int n = left.size(), m = right.size();
    while (i != n || j != m) {
        if (j == m || (i != n && left[i] <= right[j]))
            v[l++] = left[i++];
        else
        	v[l++] = right[j++];
    }
}

void _merge_sort(vector<int>& v, int l, int r) {
	if (l < r) {
		int mid = (l + r) / 2;
		_merge_sort(v, l, mid);
		_merge_sort(v, mid+1, r);
		_merge(v, l, mid, r);
	}
}

void merge_sort(vector<int>& v) {
	int n = v.size();
	_merge_sort(v, 0, n-1);
}

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);
	vector<int> v{3, 1, 2, 3, 4, 6, 1, 3, 4, 2, 5, 6, 2, 3};
	merge_sort(v);
	for (int i: v)
		cout << i << ' ';
	cout << '\n';
	return 0;
}