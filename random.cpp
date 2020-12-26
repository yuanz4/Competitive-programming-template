#include <bits/stdc++.h>
using namespace std;

unsigned seed = chrono::system_clock::now().time_since_epoch().count();
mt19937_64 rng(seed);
// mt19937 rng(seed);

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);
	cout << rng() << '\n';
	return 0;
}