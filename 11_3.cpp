// 11.3 Given a sorted array of n integers that has been rotated an unknown
// number of times, write code to find an element in the array. You may assume
// that the array was originally sorted in increasing order.
// EXAMPLE
// Input: find 5 in {15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14}
// Output: 8 (the index of 5 in the array)

#include <iostream>
using namespace std;

int bin_search(int *a, int l, int r, int n) {
	if(l == r)
		return (a[l] == n) ? l : (-1);
	if((r - l) == 1) {
		if(a[l] == n)
			return l;
		if(a[r] == n)
			return r;
		return (-1);
	}
	int mid = (l + r) / 2;
	if(n <= a[mid])
		return bin_search(a, l, mid, n);
	else
		return bin_search(a, mid + 1, r, n);
}

int search(int *a, int size, int n) {
	int border = -1;
	for(int i = 1; i < size; i ++) {
		if(a[i - 1] > a[i]) {
			border = i;
			break;
		}
	}

	// The array is not rotated: use regular bin search
	if(border == (-1))
		return bin_search(a, 0, size - 1, n);

	// Search in the left sorted part of the array
	int l_ret = bin_search(a, 0, border - 1, n);
	if(l_ret != (-1))
		return l_ret;

	// Search in the right sorted part of the array
	int r_ret = bin_search(a + border, 0, size - border - 1, n);
	if(r_ret != (-1))
		return (border + r_ret);

	// The item is not found
	return -1;
}

int main(void) {

	{ // 0
		int a[] = {1, 3, 4, 5, 7, 10, 14, 15, 16, 19, 20, 25};
		int size = sizeof(a) / sizeof(a[0]);
		int res = search(a, size, 5);
		if(res != 3)
			cout << "ERROR0" << endl;
	}

	{ // 1
		int a[] = {15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14};
		int size = sizeof(a) / sizeof(a[0]);
		int res = search(a, size, 5);
		if(res != 8)
			cout << "ERROR1" << endl;
	}

	{ // 3
		int a[] = {25, 1, 3, 4, 5, 7, 10, 14, 15, 16, 19, 20};
		int size = sizeof(a) / sizeof(a[0]);
		int res = search(a, size, 7);
		if(res != 5)
			cout << "ERROR3" << endl;
	}

	{ // 4
		int a[] = {3, 4, 5, 7, 10, 14, 15, 16, 19, 20, 25, 1};
		int size = sizeof(a) / sizeof(a[0]);
		int res = search(a, size, 7);
		if(res != 3)
			cout << "ERROR4" << endl;
	}

	{ // 5
		int a[] = {1, 3, 4, 5, 7, 10, 14, 15, 16, 19, 20, 25};
		int size = sizeof(a) / sizeof(a[0]);
		int res = search(a, size, 50);
		if(res != (-1))
			cout << "ERROR5" << endl;
	}

	{ // 6
		int a[] = {15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14};
		int size = sizeof(a) / sizeof(a[0]);
		int res = search(a, size, 50);
		if(res != (-1))
			cout << "ERROR6" << endl;
	}
	cout << "OK" << endl;
	return 0;
}
