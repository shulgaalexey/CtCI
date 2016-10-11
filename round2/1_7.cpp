#include <iostream>
using namespace std;

int main(void) {

	const int M = 6;
	const int N = 5;
	int m[M][N] = {
		{1, 2, 3, 4, 5},
		{6, 7, 8, 0, 9},
		{1, 1, 2, 3, 4},
		{5, 0, 6, 7, 8},
		{9, 2, 1, 2, 3},
		{4, 5, 6, 7, 8}};

	int raws[M] = {0};
	int cols[N] = {0};

	for(int i = 0; i < M; i ++) {
		for(int j = 0; j < N; j ++) {
			if(!m[i][j]) {
				raws[i] = 1;
				cols[j] = 1;
			}
		}
	}

	// We can use first row and first column to maintain the falgs
	// meaning, that the row/column should be nullified

	for(int i = 0; i < M; i ++) {
		if(!raws[i])
			continue;
		for(int j = 0; j < N; j ++)
			m[i][j] = 0;
	}

	for(int j = 0; j < N; j ++) {
		if(!cols[j])
			continue;
		for(int i = 0; i < M; i ++)
			m[i][j] = 0;
	}

	for(int i = 0; i < M; i ++) {
		for(int j = 0; j < N; j ++)
			cout << m[i][j] << " ";
		cout << endl;
	}

	return 0;
}
