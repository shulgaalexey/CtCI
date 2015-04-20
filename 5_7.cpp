// 5.7 An array A contains all the integers from 0 to n, except for one number which
// is missing. In this problem, we cannot access an entire integer in A with a single operation.
// The elements of A are represented in binary, and the only operation we can use to access
// them is "fetch the jth bit of A[i]", which takes constant time. Write code to find the missing
// integer. Can you do it in O(n) time?
#include <iostream>
#include <vector>
using namespace std;

int fetch(int n, int bit) {
	return (n >> bit) & 1;
}

int find_missing(vector<int> A) {
	int n = int(A.size());
	int m = n + 1;
	long long sum_to_be = (m * (m - 1)) / 2;
	int log = 1;
	while(n) { n >>= 1; log ++; }
	long long sum = 0;
	for(size_t i = 0; i < A.size(); i ++)
		for(int j = 0; j < log; j ++)
			sum += fetch(A[i], j) << j;
	return sum_to_be - sum;
}

int main(void) {
	bool ok = true;

	{
		int a[] = {0, 1, 2, 3, 5};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		ok &= find_missing(A) == 4;
	}

	{
		int a[] = {1, 3, 2, 5, 7, 6, 0};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		ok &= find_missing(A) == 4;
	}

	if(!ok) cout << "ERROR!" << endl;
	return 0;
}
