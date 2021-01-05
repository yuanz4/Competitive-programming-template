// fast for multiple query, logn for each. Use sieve,
// smallest prime factor and wheel factorization of 2

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
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

map<int, int> factorization(int i) {
	map<int, int> m;
	while (i != 1) {
		m[spf[i]]++;
		i /= spf[i];
	}
	return m;
}

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);
	sieve();
	map<int, int> m = factorization(5408);
	for (auto& i: m)
		cout << i.first << " " << i.second << '\n';
	return 0;
}