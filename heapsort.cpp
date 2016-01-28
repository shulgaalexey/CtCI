#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <algorithm>

using namespace std;

void trace(int *a, int n) {
	for(int i = 0; i < n; i ++)
		cout << setw(2) << a[i] << " ";
	cout << endl;
}

void swap(int *a, int i, int j) {
	int tmp = a[i];
	a[i] = a[j];
	a[j] = tmp;
}

void max_heapify(int *a, int i, int n) {
	int left = 2 * i + 1;
	if((left < n) && (a[i] <= a[left])) {
		swap(a, i, left);
		max_heapify(a, left, n);
	}

	int right = 2 * i + 2;
	if((right < n) && (a[i] <= a[right])) {
		swap(a, i, right);
		max_heapify(a, right, n);
	}
}

void heapsort(int *a, int n) {
	if(n == 1)
		return;

	// Pre-heapify
	for(int i = int(n / 2); i >= 0; i --)
		max_heapify(a, i, n);

	// Sort: continuously extract a root (which is max) and put it to the
	//end of the array; decrement the hipyfied array length on each step
	int cur_len = n;
	for(int i = 0; i < n; i ++) {
		swap(a, 0, cur_len - 1);
		cur_len --;
		max_heapify(a, 0, cur_len);
	}
}

int main(void) {
	int a[] = {3, 9, 4, 2, 7, 8, 6, 1, 5};
	heapsort(a, 9);
	trace(a, 9);

	srand(time(NULL));
	bool error = false;
	for(int test = 0; test < 50; test ++) {
		//cout << "Test: " << test << "..." << endl;
		const int N = 100;
		int a[N] = {0};
		for(int i = 0; i < N; i ++)
			a[i] = rand() % (2 * N);
		heapsort(a, N);
		//trace(a, N);

		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		std::sort(A.begin(), A.end());
		for(size_t i = 0; i < A.size(); i ++) {
			if(A[i] != a[i]) {
				cout << "Error" << endl;
				error = true;
			}
		}
	}
	if(!error)
		cout << "OK" << endl;
	return 0;
}
