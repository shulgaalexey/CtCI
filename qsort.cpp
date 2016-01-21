#include <iostream>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

void trace(int *a, int min_idx, int max_idx, int n) {
	return;
	for(int i = 0; i < min_idx; i ++)
		cout << setw(2) << "__" << " ";
	for(int i = min_idx; i <= max_idx; i ++)
		cout << setw(2) << a[i] << " ";
	for(int i = (max_idx + 1); i < n; i ++)
		cout << setw(2) << "__" << " ";
	cout << endl;
}

// Arg n is only for tracing purpose
void qsort(int *a, int min_idx, int max_idx, int n) {
	if(min_idx >= max_idx)
		return;

	//cout << "Recursion: min_idx = " << min_idx << " max_idx = "
	//	<< max_idx << endl;
	trace(a, min_idx, max_idx, n);
	//usleep(1 * 100000);

	int lo = min_idx;
	int hi = max_idx;
	int pivot = a[(min_idx + max_idx) / 2];
	while(lo <= hi) {
		while(a[lo] < pivot)
			lo ++;
		while(a[hi] > pivot)
			hi --;
		if(lo <= hi) {
			int tmp = a[lo];
			a[lo] = a[hi];
			a[hi] = tmp;
			lo ++;
			hi --;
		}
		trace(a, min_idx, max_idx, n);
		//usleep(1 * 100000);
	}
	qsort(a, min_idx, lo - 1, n);
	qsort(a, lo, max_idx, n);
}

int main(void) {
	int a[] = {3, 9, 4, 2, 7, 8, 6, 1, 5};
	qsort(a, 0, 8, 9);
	trace(a, 0, 8, 9);

	srand(time(NULL));
	for(int test = 0; test < 50; test ++) {
		cout << "Test: " << test << "..." << endl;
		const int N = 100;
		int a[N] = {0};
		for(int i = 0; i < N; i ++)
			a[i] = rand() % (2 * N);
		qsort(a, 0, N - 1, N);
		trace(a, 0, N - 1, N);

		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		std::sort(A.begin(), A.end());
		for(size_t i = 0; i < A.size(); i ++) {
			if(A[i] != a[i])
				cout << "Error" << endl;
		}
	}
	return 0;
}
