#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

random_device rd;
mt19937 rng(rd());

int random(int n) {
	return rng() % n;
}

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);

    cout << random(100) << endl;

	return 0;
}