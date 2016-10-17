#include <iostream>
using namespace std;

int main(void) {
	int n = 0b011001010;

	// Flippong odd and even bits:
	n = (((n & 0xAAAAAAAA) >> 1) | ((n & 0x55555555) << 1));
	cout << n << endl;
	return 0;
}


