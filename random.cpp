#include <bits/stdc++.h>
using namespace std;

random_device rd;
mt19937_64 rng(rd());
// mt19937 rng(rd());

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);
	cout << rng() << '\n';
	return 0;
}