#include <bits/stdc++.h>
using namespace std;

void max_heapify(vector<int>& v, int start, int end) {
    int dad = start;
    int son = dad * 2 + 1;
    while (son <= end) {
        if (son + 1 <= end && v[son] < v[son + 1])
            son++;
        if (v[dad] > v[son])
            return;
        else {
            swap(v[dad], v[son]);
            dad = son;
            son = dad * 2 + 1;
        }
    }
}

void heap_sort(vector<int>& v) {
    int n = v.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        max_heapify(v, i, n - 1);
    for (int i = 0; i < n; i++)
        cout << i << ' ';
    cout << '\n';
    for (int i: v)
        cout << i << ' ';
    cout << '\n';
    for (int i = n - 1; i > 0; i--) {
        swap(v[0], v[i]);
        max_heapify(v, 0, i - 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    vector<int> v{3, 1, 2, 3, 4, 6, 1, 3, 4, 2, 5, 6, 2, 3};
    heap_sort(v);
    for (int i: v)
        cout << i << ' ';
    cout << '\n';
    return 0;
}