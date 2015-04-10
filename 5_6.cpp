// 5.6 Write a programm to swap odd and even bits in an integer with as few instructions
// as possible (e.g. bit 0 and bit 1 are swapped, bit 2 and bit 3 are swapped, and so on)
#include <iostream>
using namespace std;

int swap(int n) {
	int i = 0, t = 0; // cur pos and tail pair of bits
	while(n >> i) {
		t = (n >> i) & 3;
		if(t && (t ^ 3)) n ^= 3 << i;
		i += 2;
	}
	return n;
}

int main(void) {
	bool ok = true;
	ok &= swap(0b010101) == 0b101010;
	ok &= swap(0) == 0;
	ok &= swap(1) == 0b10;
	ok &= swap(0b11000110) ==
		0b11001001;
	if(ok) cout << "ERROR!" << endl;
}
