// combination的递归表达式，杨辉三角

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAX = 55;
ll c[MAX][MAX];

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);
	for (int i = 0; i < MAX; i++) {
    	c[i][0] = c[i][i] = 1;
    	for (int j = 1; j < i; j++)
    		c[i][j] = c[i-1][j-1] + c[i-1][j];
    }
    cout << c[50][25] << '\n';
	return 0;
}