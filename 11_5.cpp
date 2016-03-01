// Given a sorted array of strings which is intersperced with empty strings,
// write a method to find the location of a given string.
// EXAMPLE
// input: find "ball" in {"at", "", "", "", "ball", "", "", "car", "", "",
//                        "dad", "", ""}
// Output: 4
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int bin_search(const vector<string> &A, const string &s, int l, int r) {
	int center = (l + r) / 2;
	if(A[center] == s)
		return center;

	int left = center;
	while((left >= l) && (A[left].empty()))
		left --;
	if((left >= l) && (A[left] >= s)) {
		int ret = bin_search(A, s, l, left);
		if(ret >= left)
			return ret;
	}

	int right = center + 1;
	while((right <= r) && A[right].empty())
		right ++;
	if((right <= r) && (A[right] <= s)) {
		int ret = bin_search(A, s, r, right);
		if(ret >= r)
			return ret;
	}

	return -1;
}

int main(void) {
	const char *a[] = {"at", "", "", "", "ball", "", "", "car", "", "",
		"dad", "", ""};
	vector<string> A;
	for(int i = 0; i < int(sizeof(a) / sizeof(a[0])); i ++)
		A.push_back(a[i]);
	int ret = bin_search(A, "ball", 0, int(A.size()) - 1);
	cout << ret << endl;
	if(ret != 4)
		cout << "ERROR" << endl;
	return 0;
}
