// 17.11
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <map>
using namespace std;

int rand5() {
	return rand() % 5;
}

int rand7() {
	while(true) {
		int num = rand5() * 5 + rand5();
		if(num < 21)
			return (num % 7);
	}
}

int main(void) {
	srand(time(NULL));

	map<int, int> m;
	const int N = 1000;
	for(int i = 0; i < N; i ++) {
		int r = rand7();
		if(m.count(r) <= 0)
			m[r] = 0;
		else
			m[r] ++;
	}

	for(int i = 0; i < 7; i ++) {
		double p = .0;
		if(m.count(i) <= 0)
			continue;
		p = 1. * m[i] / N;
		cout << i << ": " << p << " err: " << double(100. * (1. / 7 - p)) << "%" << endl;
	}

	return 0;
}
