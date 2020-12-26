#include <bits/stdc++.h>
using namespace std;

const int n = 100;
const int len = 30;
const int letter = 26;

const int mx = n * len * letter;
int nxt[mx][letter];
bool exist[mx];
int cnt;

void insert(string s) {
	int p = 0;
	int l = s.size();
	for (int i = 0; i < l; i++) {
		int c = s[i] - 'a';
		if (!nxt[p][c])
			nxt[p][c] = ++cnt;
		p = nxt[p][c];
	}
	exist[p] = 1;
}

bool find(string s) {
	int p = 0;
	int l = s.size();
	for (int i = 0; i < l; i++) {
		int c = s[i] - 'a';
		if (!nxt[p][c])
			return false;
		p = nxt[p][c];
	}
	return exist[p];
}

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);
	insert("abcde");
	insert("bsdaddd");
	insert("abcess");
	cout << find("abcde") << '\n';
	return 0;
}