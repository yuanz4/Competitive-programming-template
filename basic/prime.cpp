// sieve of eratosthenes, O(n*ln(ln(sqrt(n))) + o(n))
// in [1...n], there are n/(ln(n)-1) prime numbers

#include <bits/stdc++.h>
using namespace std;

vector<bool> sieve(int n) {
	vector<bool> is_prime(n+1, true);
	is_prime[0] = is_prime[1] = false;
	for (int i = 2; i*i <= n; i++) {
		if (is_prime[i]) {
			for (int j = i*i; j <= n; j += i)
				is_prime[j] = false;
		}
	}
	return is_prime;
}

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n = 11;
	vector<bool> is_prime = sieve(n);
	for (int i = 0; i <= n; i++) {
		if (is_prime[i])
			cout << i << ' ';
	}
	cout << '\n';
	return 0;
}
