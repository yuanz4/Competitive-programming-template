#include <cstdlib>
#include <chrono>
#include <iostream>

using namespace std;

int main() {
	int T = 10;
	system("g++ generate.cpp -std=c++17 -o bin/generate");
	system("g++ sol.cpp -std=c++17 -o bin/sol");
	system("g++ bf.cpp -std=c++17 -o bin/bf");
	for (int t = 1; t <= T; t++) {
		system("./bin/generate > bin/data.in");
		auto st = chrono::high_resolution_clock::now();
		system("./bin/sol < bin/data.in > bin/data.out");
		auto ed = chrono::high_resolution_clock::now();
		system("./bin/bf < bin/data.in > bin/data.ans");
		if (system("diff bin/data.out bin/data.ans")) {
			cout << "Wrong Answer" << '\n';
			return 0;
		} else {
			auto seconds = chrono::duration_cast<chrono::duration<float>>(ed-st);
			cout << "Accepted, test #" << t << ", duration " << seconds.count() << "s\n";
		}
	}

	return 0;
}