// 5.3 Given a positive integer, print the next smallest and next larges number
// that have the same number of 1 bits in their binary representation.
#include <iostream>
#include <stdexcept>
using namespace std;

int find_next_smallest(int n) {
	// 1. Find first 1
	int i = 0;
	while(((n >> i) & 1) != 1) {
		i ++;
		if(i > int(sizeof(n) * 8))
			throw out_of_range("find_next_smallest, find first 1");
	}

	// 2. Find previous 0
	int j = i - 1;
	if(j < 0)
		throw out_of_range("find_next_smallest, before find previous 0");
	while(((n >> j) & 1) != 0) {
		j --;
		if(j < 0)
			throw out_of_range("find_next_smallest, find previous 0");
	}

	n &= ~(1 << i);	// 3.a Exchange first 1 with 0
	n |= 1 << j;	// 3.b Exchange previous 0 with 1
	return n;
}

int find_next_largest(int n) {
	// 1. Find first 1
	int i = 0;
	while(((n >> i) & 1) != 1) {
		i ++;
		if(i > int(sizeof(n) * 8))
			throw out_of_range("find_next_largest, find first 1");
	}

	// 2. Find next 0
	int j = i + 1;
	if(j > int(sizeof(n) * 8))
		throw out_of_range("find_next_largest, before find next 0");
	while(((n >> j) & 1) != 0) {
		j ++;
		if(j > int(sizeof(n) * 8))
			throw out_of_range("find_next_largest, find next 0");
	}

	n &= ~(1 << i);	// 3.a Exchange first 1 with 0
	n |= 1 << j;	// 3.b Exchange next 0 with 1
	return n;
}

int main(void) {
	if(find_next_smallest(0b101100) != 0b101010) cout << "PROBLEM!" << endl;
	if(find_next_largest(0b101100) != 0b111000) cout << "PROBLEM!" << endl;
	return 0;
}
