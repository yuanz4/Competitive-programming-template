// b, m互质，并且b|a，则存在x使得a/b同余a*x(mod m)，记录x为b^(-1)(mod m)
// 当模数m为质数时，b^(p-2)为乘法逆元
// 在用分数表示P/Q，一般会要求给出P*Q^(-1)(mod m)，P和Q不一定要coprime
// 令该操作为f()，则f(A/B+C/D)(mod m)=f(A/B)+f(C/D)%m，分数间加法很简单

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll mod = 1000000007;

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

ll fraction(ll p, ll q) {
	ll inv = powmod(q, mod-2);
	return p * inv % mod;
}

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);
	int p = 90, q = 2;
	cout << "without: " << (p / q) % mod << '\n';
	ll x = powmod(q, mod-2);
	cout << "with: " << (p * x) % mod << '\n';
	int A = 2, B = 4, C = 5, D = 6;
	cout << "add then convert " << fraction(4, 3) << '\n';
	cout << "convert then add " << (fraction(2, 4) + fraction(5, 6)) % mod << '\n';
	return 0;
}