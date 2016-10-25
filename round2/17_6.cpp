#include <iostream>
using namespace std;

void find_mn(int *a, const int N, int *m, int *n) {
	*m = -1;
	*n = -1;

	int k = -1;
	for(int i = 1; i < N; i ++) {
		if(a[i] < a[i - 1]) {
			k = i;
			break;
		}
	}

	if(k < 0)
		return; // initially sorted array


	for(int i = (N - 1); i >= k; i --) {
		if(a[i] < a[i - 1]) {
			*n = i + 1;
			break;
		}
	}

	int min_val = 1000000;
	for(int i = k; i <= (*n); i ++) {
		if(a[i] < min_val)
			min_val = a[i];
	}

	for(int i = (k - 1); i >= 0; i --) {
		if(a[i] < min_val) {
			*m = i + 1;
			break;
		}
	}
}

int main(void) {
	int a[] = {1, 2, 4, 7, 10, 11, 7, 12, 6, 7, 16, 18, 19};
	const int N = int(sizeof(a) / sizeof(a[0]));

	int m = 0;
	int n = 0;
	find_mn(a, N, &m, &n);

	cout << m << ", " << n << endl;
	return 0;
}

