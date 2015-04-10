//  5.5 Write a function to determine the number of bits you would need to flip to
//  convert integer A to integer B.
//  EXAMPLE
//  Input: 29 (or: 11101), 15 (or:  01111)
//  Output: 2
#include <iostream>
using namespace std;

int get_flip_count(int a, int b) {
	int cnt = 0;
	while(a || b) {
		cnt += (a & 1) ^ (b & 1);
		a >>= 1;
		b >>= 1;
	}
	return cnt;
}

int main(void) {
	bool ok = true;
	ok &= get_flip_count(0b11101, 0b01111) == 2;
	ok &= get_flip_count(0, 0) == 0;
	ok &= get_flip_count(1, 1) == 0;
	ok &= get_flip_count(0b101, 0b101) == 0;
	ok &= get_flip_count(0b10, 0b01) == 2;
	if(!ok) cout << "PROBLEM!" << endl;
	return 0;
}
