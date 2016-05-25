// 17.8
// You are given an array of integers (both positive and negative). Find the
// contiguous sequence with the largest sum. Return the sum.
// EXAMPLE
// Input: 2, -8, 3, -2, 4, -10
// Output: 5 (i.e. {3, -2, 4})

#include <iostream>
using namespace std;

int max_sum(int *a, const int n) {
	int sum = 0;
	int max = 0; // May be assigned with a max item of the array
	for(int i = 0; i < n; i ++) {
		sum += a[i];
		if(sum < 0)
			sum = 0;
		max = (max > sum) ? max : sum;
	}
	return max;
}

int main(void) {
	{ // 1
		int a[] = {2, -8, 3, -2, 4, -10};
		const int n = sizeof(a) / sizeof(a[0]);
		const int max = max_sum(a, n);
		if(max != 5)
			cout << "ERROR1" << endl;
	}

	{ // 2
		int a[] = {2, 3, -8, -1, 2, 4, -2, 3};
		const int n = sizeof(a) / sizeof(a[0]);
		const int max = max_sum(a, n);
		if(max != 7)
			cout << "ERROR2" << endl;
	}
	return 0;
}
