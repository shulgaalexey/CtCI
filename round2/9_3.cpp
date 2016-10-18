#include <iostream>
using namespace std;

int find_magic_bf(int *arr, const int n) {
	for(int i = 0; i < n; i ++)
		if(arr[i] == i)
			return i;
	return 1000000000; // error
}

int find_magic_bs(int *arr, const int n, const int i, const int j) {
	if((i < 0) || (j < i) || (j >= n))
		return 1000000000; // error
	int mid = (i + j) / 2;
	if(arr[mid] == mid)
		return mid;
	else if(arr[mid] > mid)
		return find_magic_bs(arr, n, i, mid - 1);
	else
		return find_magic_bs(arr, n, mid + 1, j);
}

int main(void) {
	const int n = 8;
	int arr[] = {-5, -2, 0, 1, 3, 5, 6, 9, 10};
	cout << find_magic_bf(arr, n) << " | "
		<< find_magic_bs(arr, n, 0, n - 1) << endl; // 5
	return 0;
}
