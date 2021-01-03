// 根本思想是divide and conquer
// 1. 将系数表示法(coefficient)转为点值表示法(sample)
// 在sample location的选取上用roots of unity, 这样可以保证递归中下一层的x"和
// 上一层的x'满足(x')^2=x"。因为x"为1的n/2次root，x'为1的n次root。这个过程叫DFT
// 可以直接assign a[i+j]与a[i+j+len/2]是因为
// cos(2*pi/n+pi)+i*sin(2*pi/n+pi)=cos(2*pi/n)-i*sin(2*pi/n)
// 2. 将点值相乘，sample点相同的x可以直接将y相乘
// 3. 做IDFT，转换回系数表示法，根据范德蒙矩阵，与DFT十分类似，共轭并除以n
// 4. optimization, 用butterfly transform将recursive变成iterative

#include <bits/stdc++.h>
using namespace std;

using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd> & a, bool invert) {
    int n = a.size();

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert) {
        for (cd & x : a)
            x /= n;
    }
}

vector<int> multiply(vector<int> const& a, vector<int> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) 
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    vector<int> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real());
    return result;
}

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);
	vector<int> a{1, 3, 4, 2, 2};
	vector<int> b{1, 1};
	vector<int> v = multiply(a, b);
	for (auto& i: v)
		cout << i << ' ';
	cout << '\n';
	return 0;
}