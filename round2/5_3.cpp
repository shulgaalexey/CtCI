#include <iostream>
using namespace std;

int set(int n, int i, bool b) {
	if(b)
		return (n | (1 << i));
	else
		return (n & (~(1 << i)));
}

int main(void) {
	int b = 0b01011;

	// find smallest
	int b1 = b;
	for(int i = 0; i < 32; i ++) {
		if(b1 & 1)
			b1 >>= 1;
		else {
			if(!b1) {
				cout << "ERROR1" << endl;
				break;
			}

			b1 >>= 1;
			int j = i + 1;
			for(; j < 32; j ++) {
				if(b1 & 1)
					break;
				else
					b1 >>= 1;
			}

			int smallest = set(b, j, false);
			smallest = set(smallest, i, true);
			cout << smallest << endl;
			break;
		}
	}

	// find largest
	// similar, but change first 0 with rightmost 1

	return 0;
}
