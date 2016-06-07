// 18.1 Write a function that adds two numbers. You should not use + or any
// arithmetic operqtors.
#include <iostream>
using namespace std;

typedef unsigned char byte;

byte add(byte a, byte b) {
	if(b == 0)
		return a;
	byte sum = a ^ b;
	byte shift = (a & b) << 1;
	return add(sum, shift);
}

int main(void) {
	for(byte a = 0; a < 100; a ++) {
		for(byte b = 0; b < 100; b ++) {
			if(add(a, b) != (a + b)) {
				cout << "ERROR: " << int(a) << " + " << int(b)
					<< " = " << int(add(a, b)) << endl;
				return 1;
			}
		}
	}
	cout << "OK" << endl;
	return 0;
}
