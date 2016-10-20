#include <iostream>
using namespace std;

const int N = 8;
const int M = 3;

int A[N + M] = {1, 2, 4, 5, 6, 8, 9, 11};
int B[M] = {3, 7, 10};

void merge(void) {
	int pa = N - 1;
	int pb = M - 1;
	int pins = N + M - 1;

	while(pb >= 0)
		if(A[pa] > B[pb])
			A[pins --] = A[pa --];
		else
			A[pins --] = B[pb --];
}

int main(void) {
	merge();
	for(int i = 0; i < (M + N); i ++)
		cout << A[i] << " ";
	cout << endl;
	return 0;
}
