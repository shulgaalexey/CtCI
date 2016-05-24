// Given an array of integers, write a method to find indices m and n such that
// if you sorted elements m through n, the entire array would be sorted.
// Minimize n - m (that is, find the smallest such sequence).
// EXAMPLE
// Input: 1, 2, 4, 7, 10, 11, 7, 12, 6, 7, 16, 18, 19
// Output: (3, 9)
#include <iostream>
using namespace std;

void solution(int *a, const int size, int *n, int *m) {
	*n = -1;
	*m = -1;
	int cur_max = a[0];
	int k = -1;

	// 1. Find left border of unsorted part
	for(int i = 1; i < size; i ++) {
		if(a[i] > cur_max) {
			cur_max = a[i];
		} else {
			k = i;
			if((*n) == 0)
				continue;
			if(a[i] < a[0]) {
				(*n) = 0;
				continue;
			}

			for(int j = 1; j < size; j ++) {
				if(a[i] <= a[j]) {
					if((*n) == -1)
						*n = j;
					else if((*n) > j)
						*n = j;
					break;
				}
			}
		}
	}

	if(k == (-1))
		return;
	if(k == (size - 1)) {
		*m = size - 1;
		return;
	}

	// 2. Find right border of unsorted part
	cur_max = a[*n];
	for(int i = (*n); i <= k; i ++) {
		if(a[i] > cur_max)
			cur_max = a[i];
	}

	for(int i = k; i < size; i ++) {
		if(a[i] >= cur_max) {
			*m = i - 1;
			return;
		}
	}
	*m = size - 1;
}

int main(void) {
	{ //1
		int a[] = {1, 2, 4, 7, 10, 11, 7, 12, 6, 7, 16, 18, 19};
		const int size = sizeof(a) / sizeof(a[0]);
		int n = 0;
		int m = 0;
		solution(a, size, &n, &m);
		cout << "(" << n << ", " << m << ")" << endl;
	}

	{ //2
		int a[] = {1, 2, 3, 4, 5};
		const int size = sizeof(a) / sizeof(a[0]);
		int n = 0;
		int m = 0;
		solution(a, size, &n, &m);
		cout << "(" << n << ", " << m << ")" << endl;
	}

	{ //3
		int a[] = {5, 4, 3, 2, 1};
		const int size = sizeof(a) / sizeof(a[0]);
		int n = 0;
		int m = 0;
		solution(a, size, &n, &m);
		cout << "(" << n << ", " << m << ")" << endl;
	}

	{ //3
		int a[] = {1, 2, 4, 7, 10, 11, 7, 12, 6, 7, 16, 8, 19};
		const int size = sizeof(a) / sizeof(a[0]);
		int n = 0;
		int m = 0;
		solution(a, size, &n, &m);
		cout << "(" << n << ", " << m << ")" << endl;
	}

	return 0;
}
