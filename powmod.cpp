// 快速幂，binary exponentiation

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll mod = 1e9+7;

ll powmod(ll a, ll b) {
	ll res = 1;
	a %= mod;
	for (; b; b >>= 1) {
		if (b & 1)
			res = res * a % mod;
		a = a * a % mod;
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);
	cout << powmod(2, 5) << '\n';
	return 0;
}