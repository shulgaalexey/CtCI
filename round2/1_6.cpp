#include <iostream>
using namespace std;

int main(void) {
	const int N = 4;
	int M[N][N] = {
		{ 1, 2, 3, 4},
		{ 2, 3, 4, 5},
		{ 3, 4, 5, 6},
		{ 4, 5, 6, 7}};

	for(int layer = 0; layer < (N / 2); layer ++) {
		int first = layer;
		int last = N - 1 - layer;
		for(int i = first; i < last; i ++) {
			int offset = i - first;

			int top = M[first][i];
			M[first][i] = M[last - offset][first];
			M[last - offset][first] = M[last][last - offset];
			M[last][last - offset] = M[i][last];
			M[i][last] = top;
		}
	}

	for(int i = 0; i < N; i ++) {
		for(int j = 0; j < N; j ++) {
			cout << M[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}
