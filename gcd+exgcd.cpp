// 最后需要a/d并且b/d，要求出一般解，可以将x+=z*b或者y-=z*a，z为整数

#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
	if (b == 0)
		return a;
	return gcd(b, a%b);
}

int exgcd(int a, int b, int& x, int& y) {
	if (b == 0) {
		x = 1, y = 0;
		return a;
	}
	int d = exgcd(b, a%b, x, y);
	int z = x;
	x = y;
	y = z - y * (a / b);
	return d;
}

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);
	int d, x, y;
	d = exgcd(999999, 524287427135, x, y);
	cout << d << " " << x << " " << y << '\n';
	return 0;
}