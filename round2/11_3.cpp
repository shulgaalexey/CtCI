#include <iostream>
using namespace std;

const int N = 12;
int a[N] = {15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14};

int bs(const int left, const int right, const int v) {
	if((left < 0) || (right >= N) || (left > right))
		return -1;

	const int mid = (left + right) / 2;
	if(a[mid] == v)
		return mid;
	else if(a[right] < a[left]) {
		int ret = bs(left, mid - 1, v);
		if(ret >= 0)
			return ret;
		else
			return bs(mid + 1, right, v);
	} else {
		if(v < a[mid])
			return bs(left, mid - 1, v);
		else
			return bs(mid + 1, right, v);
	}
}

int main(void) {
	const int r = bs(0, N - 1, 5);
	cout << r << endl; //  expected 8
	return 0;
}
