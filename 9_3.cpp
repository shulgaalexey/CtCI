// 9.3 A magic index in an array A[0...n01] is defined to be an index such that
// A[i] = i. Given a sorted array of distinct integers, write a method to find a
// magic index,  if one exists, in array A.
// FOLLOW UP
// What if the values are not distinct?
#include <iostream>
#include <vector>
#include <map>
using namespace std;

// Idea: binary search
vector<int> _result;
void find_magic_indexes(int *v, const int N, const int shift) {
	if(N == 2) {
		if(v[0] == shift)
			_result.push_back(shift);
		if(v[1] == (shift + 1))
			_result.push_back(shift + 1);
		return;
	}
	if(N == 1) {
		if(v[0] == shift)
			_result.push_back(shift);
		return;
	}

	int l = 0;
	int r = N - 1;
	int m = r / 2;

	// Find magic indexes in the left half
	if(v[l] <= shift) // Check if we have a chance to find a magic index
		find_magic_indexes(v, m, shift);

	// Find magic indexes in the right half
	if(v[r] >= (r + shift)) // Check if we have a chance to find a magic index
		find_magic_indexes(v + m, N - m, m + shift);
}

// Brute-force approach
map<int, bool> _result_bf;
void find_magic_indexes_bf(int *v, const int N) {
	for(int i = 0; i < N; i ++)
		if(v[i] == i )
			_result_bf[i] = true;
}

int main(void) {
	int v[] = { -10, -8, -7, -6, 4, 4, 5, 7, 9, 9, 10};
	//            0   1   2   3  4  5  6  7  8  9  10
	const int N = sizeof(v) / sizeof(v[0]);
	find_magic_indexes(v, N, 0);
	find_magic_indexes_bf(v, N);

	if(_result_bf.count(4) < 0) cout << "ERROR" << endl;
	if(_result_bf.count(7) < 0) cout << "ERROR" << endl;
	if(_result_bf.count(9) < 0) cout << "ERROR" << endl;
	if(_result_bf.count(10) < 0) cout << "ERROR" << endl;

	/*if(_result.size() != _result_bf.size()) {
	  cout << "ERROR!" << endl;
	  return -1;
	  }*/

	for(size_t i = 0; i < _result.size(); i ++) {
		const int magic_index = _result[i];
		cout << magic_index << endl;
		if(_result_bf.count(magic_index) < 0)
			cout << "ERROR! " << magic_index << endl;
	}

	return 0;
}
