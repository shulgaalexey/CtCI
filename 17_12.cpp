// 17.12
// Design an algorithm to find all pairs of integers within an array which sum
// to a specified value.
#include <iostream>
#include <map>
using namespace std;

void find_pairs(int *a, const int N, const int S) {
	map<int, int> m;
	for(int i = 0; i < N; i ++)
		m[a[i]] = a[i];

	for(int i = 0; i < N; i ++)
		if(m.count(S - a[i]) > 0)
			cout << a[i] << ", " << int(S - a[i]) << endl;
}

int main(void) {
	int a[] = {0, 1, 2, 3, 3, 3, 4, 5, 6, 7, 8, 9, 10};
	const int N = sizeof(a) / sizeof(a[0]);
	find_pairs(a, N, 9);

	return 0;
}
