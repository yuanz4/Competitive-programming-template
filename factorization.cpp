// fast for multiple query, logn for each. Use sieve,
// smallest prime factor and wheel factorization of 2

#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e5+7;

int spf[MAX];

void sieve() {
	spf[1] = 1;
	for (int i = 2; i < MAX; i++) {
		if (i % 2 == 0)
			spf[i] = 2;
		else
			spf[i] = i;
	}
	for (int i = 3; i * i < MAX; i += 2) {
		if (spf[i] == i) {
			for (int j = i * i; j < MAX; j += i) {
				if (spf[j] == j)
					spf[j] = i;
			}
		}
	}
}

map<int, int> factorization(int n) {
	map<int, int> m;
	while (n != 1) {
		m[spf[n]]++;
		n /= spf[n];
	}
	return m;
}

map<int, int> factorization_naive(int n) {
	map<int, int> m;
	for (int i = 2; i * i <= n; i++) {
		while (n % i == 0) {
			m[i]++;
			n /= i;
		}
	}
	if (n != 1)
		m[n]++;
	return m;
}

void print(map<int, int> m) {
	string sep = "";
	for (auto& i: m) {
		cout << sep << i.first << "^" << i.second;
		sep = " * ";
	}
	cout << '\n';
}

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n = 54000;
    print(factorization_naive(n));

	sieve();
	print(factorization(n));
	return 0;
}