// 1.6 Given an image representing by NxN matrix, where each pixel in the image is 4 bytes,
// write a method to rotate the image by 90 degrees.
// Can you do this in place?

#include <iostream>
#include <math.h>

using namespace std;

class cell {
public:
	int x;
	int y;
	int N;
public:
	void transit();
	int idx() const;
};

void cell::transit() {
	int x_old = x;
	int y_old = y;
	x = N - 1 - y_old;
	y = x_old;
}

int cell::idx() const {
	return (y * N + x);
}

void trace(int *m, const int N) {
	cout << endl;
	for(int i = 0; i < N; i ++) {
		for(int j = 0; j < N; j ++) {
			cout << m[i*N + j] << " ";
		}
		cout << endl;
	}
}

void rotate_cell(cell c, int *m) {
	int v = m[c.idx()];
	for(int i = 0; i < 4; i ++) {
		c.transit();
		const int tmp = m[c.idx()];
		m[c.idx()] = v;
		v = tmp;
	}
}

void rotate_inplace(int *m, const int N) {
	for(int i = 0; i < ceil(1.0 * N / 2); i ++) {
		cell c = {i, i, N};
		const int steps = N - 2 * i -1;
		for(int step = 0; step < steps; step ++) {
			rotate_cell(c, m);
			//trace(m, N);
			c.x ++;
		}
	}
}

void rotate_copy(int *m, const int N) {
	int *m_new = new int[N*N];
	for(int i = 0; i < N; i ++) {
		for(int j = 0; j < N; j ++) {
			int jn = N - 1 - i;
			int in = j;
			m_new[in * N + jn] = m[i * N + j];
		}
	}
	for(int i = 0; i < (N*N); i ++)
		m[i] = m_new[i];
	delete [] m_new;
}

bool compare(int *m, int *t, const int N) {
	bool equal = true;
	for(int i = 0; i < N; i ++) {
		for(int j = 0; j < N; j ++) {
			if(m[i*N + j] != t[i*N + j]) {
				cout << "Error on cell: [" << i << ", " << j << "]";
				cout << " " << m[i*N + j] << " != " << t[i*N + j] << endl;
				equal = false;
			}
		}
	}
	return equal;
}

int main() {
	{ // 1 test
		const int N = 4;
		int m[N][N] = {
				{ 1, 2, 3, 4},
				{ 2, 3, 4, 5},
				{ 3, 4, 5, 6},
				{ 4, 5, 6, 7}};
		rotate_inplace((int *)m, N);
		trace((int *)m, N);
		int t[N][N] = {
				{ 4, 3, 2, 1},
				{ 5, 4, 3, 2},
				{ 6, 5, 4, 3},
				{ 7, 6, 5, 4}};

		if(!compare((int *)m, (int *)t, N)) cout << "PROBLEM!" << endl;
	}

	{ // 2 test
		const int N = 3;
		int m[N][N] = {
				{ 1, 2, 3},
				{ 4, 5, 6},
				{ 7, 8, 9}};
		rotate_inplace((int *)m, N);
		trace((int *)m, N);
		int t[N][N] = {
				{ 7, 4, 1},
				{ 8, 5, 2},
				{ 9, 6, 3}};

		if(!compare((int *)m, (int *)t, N)) cout << "PROBLEM!" << endl;
	}

	{ // 1.a test
		const int N = 4;
		int m[N][N] = {
				{ 1, 2, 3, 4},
				{ 2, 3, 4, 5},
				{ 3, 4, 5, 6},
				{ 4, 5, 6, 7}};
		rotate_inplace((int *)m, N);
		trace((int *)m, N);
		int t[N][N] = {
				{ 4, 3, 2, 1},
				{ 5, 4, 3, 2},
				{ 6, 5, 4, 3},
				{ 7, 6, 5, 4}};

		if(!compare((int *)m, (int *)t, N)) cout << "PROBLEM!" << endl;
	}

	{ // 2.a test
		const int N = 3;
		int m[N][N] = {
				{ 1, 2, 3},
				{ 4, 5, 6},
				{ 7, 8, 9}};
		rotate_inplace((int *)m, N);
		trace((int *)m, N);
		int t[N][N] = {
				{ 7, 4, 1},
				{ 8, 5, 2},
				{ 9, 6, 3}};

		if(!compare((int *)m, (int *)t, N)) cout << "PROBLEM!" << endl;
	}

	return 0;
}
