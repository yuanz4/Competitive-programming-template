// Travelling salesman: total n cities and pairwise distance
// Start from s, visit all cities and return to s
// (current city, visited cities) as state, total n*2^n states
// Total time complexity: O(n^2*2^n)

#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> dist, memo;

int tsp(int pos, int mask) {
	if (mask == (1 << n) - 1)
		return dist[pos][0];
	if (memo[pos][mask] != -1)
		return memo[pos][mask];
	int ans = INT_MAX;
	for (int i = 0; i < n; i++) {
		if (pos != i && !(mask & (1 << i)))
			ans = min(ans, dist[pos][i] + tsp(i, mask | (1 << i)));
	}
	return memo[pos][mask] = ans;
}

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);
    n = 4;
    dist.assign(n, vector<int>(n));
    memo.assign(n, vector<int>(1 << n, -1));
  //      20
  //   0------1
  //   |\35  /|
  // 42| ---- |34
  //   |/30  \|
  //   2------3
  //      12
    dist[0][1] = 20;
    dist[0][2] = 42;
    dist[0][3] = 35;
    dist[1][0] = 20;
    dist[1][2] = 30;
    dist[1][3] = 34;
    dist[2][0] = 42;
    dist[2][1] = 30;
    dist[2][3] = 12;
    dist[3][0] = 35;
    dist[3][1] = 34;
    dist[3][2] = 12;
	cout << tsp(0, 1) << '\n';
	return 0;
}