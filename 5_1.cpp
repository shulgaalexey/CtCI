// 5.1 You are given two 32-bi numbers, N and M, and two bit positions, i and j.
// Write a method to insert M into N such that M starts at bit j and ends at bit i.
// You can assume that the bits j throug i have enough space to fit all M.
// That is, if M = 10011, you can assume that there are at least 5 bits between j and i.
// You would not, for example, have j = 3 and i = 2, because M could not fully fit
// between bit 3 and bit 2.
// EXAMPLE
// Input:  N = 10000000000, M = 10011, i = 2, j = 6
// Output: N = 10001001100
#include <iostream>
using namespace std;

int insert(int N, int M, int i, int j) {
	int mask = ((-1) << (i + j)) | (~((-1) << i)); // mask: 11110000011 to clear bits j through i
	N &= mask;
	N |= M << i;
	return N;
}

int main(void) {
	int N = insert(0b10000000000, 0b10011, 2, 6);
	if(N != 0b10001001100) cout << "PROBLEM!" << endl;
	return 0;
}
