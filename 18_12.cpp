// 18.12 Given an NxN matrix of positive and negative integers, write code to
// find the submatrix with the largest possible sum.
#include <iostream>
using namespace std;

#define max(a,b) ((a>b)?a:b)

void clear_array(int *a, int N) {
	for(int i = 0; i < N; i ++)
		a[i] = 0;
}

int max_subarray(int *a, int N) {
	int max_sum = 0;
	int running_sum = 0;

	for(int i = 0; i < N; i ++) {
		running_sum += a[i];
		max_sum = max(max_sum, running_sum);
		running_sum = max(running_sum, 0);
	}
	return max_sum;
}

int max_submatrix(int *m, int N) {
	int *partial_sum = new int[N];
	int max_sum = 0;

	for(int row_start = 0; row_start < N; row_start ++) {
		clear_array(partial_sum, N);
		for(int row_end = row_start; row_end < N; row_end ++) {
			for(int col = 0; col < N; col ++)
				partial_sum[col] += m[row_end * N + col];

			int tmp_max = max_subarray(partial_sum, N);
			max_sum = max(max_sum, tmp_max);
		}
	}

	delete [] partial_sum;
	return max_sum;
}

int main(void) {
	{ // 1
		int m[] = {
			 0, -3,  2,  1,
			-7,  5, -1,  1,
			 2,  2,  6, -8,
			-3, -4, -5,  4
		};
		const int max_sum = max_submatrix(m, 4);
		cout << max_sum << endl;
		if(max_sum != 12)
			cout << "ERROR" << endl;
	}
	return 0;
}
