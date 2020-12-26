// optimized using monotonic queue

#include <bits/stdc++.h>
using namespace std;

int calc(int i, int u, int k) {
	return f[u + k*V[i]] - k*W[i];
}

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);
	cin >> n >> m;
	memset(f, 0xcf, sizeof(f));
	f[0] = 0;
	for (int i = 1; i <= n; i++) {
		cin >> V[i] >> W[i] >> C[i];
		for (int u = 0; u < V[i]; u++) {
			int l
		}
	}
	return 0;
}