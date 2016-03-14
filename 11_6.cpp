// 1.6 Given a M x N matrix in which each row and each column is sorted in
// ascending order, write a method to find an element.

#include <iostream>
using namespace std;

int *a;
int M, N, row, col;

bool search(int v) {
	int l = 0, r = N - 1, t = 0, b = M - 1;

	bool ok = true;
	while(ok) {
		ok = false;

		// 1. move l -> r
		int step = (r - l + 1) / 2;
		ok |= step;
		int pos = l;
		while(step) {
			int cur = a[t * N + pos + step];
			if(cur == v) {
				col = pos + step;
				row = t;
				return true;
			}
			if(cur < v)
				pos += step;
			step /= 2;
		}
		r = pos;

		// 2. move t -> b
		step = (b - t + 1) / 2;
		ok |= step;
		pos = t;
		while(step) {
			int cur = a[(pos + step) * N + r];
			if(cur == v) {
				col = r;
				row = pos + step;
				return true;
			}
			if(cur < v)
				pos += step;
			step /= 2;
		}
		b = pos;

		// 3. move r -> l
		step = (r - l + 1) / 2;
		ok |= step;
		pos = r;
		while(step) {
			int cur = a[b * N + pos - step];
			if(cur == v) {
				col = pos - step;
				row = b;
				return true;
			}
			if(cur > v)
				pos -= step;
			step /= 2;
		}
		l = pos;

		// 4. move b -> t
		step = (b - t + 1) / 2;
		ok |= step;
		pos = b;
		while(step) {
			int cur = a[(pos - step) * N + l];
			if(cur == v) {
				col = l;
				row = pos - step;
				return true;
			}
			if(cur > v)
				pos -= step;
			step /= 2;
		}
		t = pos;
	}
	return false;
}

int main(void) {
	int G[] = {
		15, 20, 70, 85,
		20, 35, 80, 95,
		30, 55, 95, 105,
		40, 80, 100, 120
	};
	a = (int *)G;

	M = 4;
	N = 4;
	if(!search(95))
		cout << "ERROR: not found" << endl;
	else if((row != 1) && (col != 2))
		cout << "ERROR: wrong pos" << endl;
	else
		cout << "OK" << endl;
	return 0;
}
