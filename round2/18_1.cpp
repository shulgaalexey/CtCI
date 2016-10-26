#include <iostream>
using namespace std;

int add(int a, int b) {
	int c = 0;
	int next = 0;
	int pos = 0;
	while(a | b) {
		int cur = ((a ^ b) ^ next) & 1;
		if(cur)
			c |= 1 << pos;
		pos ++;
		next = ((a & b) | (a & next) | (b & next)) & 1;
		a >>= 1;
		b >>= 1;
	}
	if(next)
		c |= 1 << pos;
	return c;
}

int main(void) {
	for(int i = 0; i < 10; i ++) {
		for(int j = 0; j < 10; j ++) {
			//cout << int(i) << " + " << int(j) << " = " << int(add(i, j)) << endl;
			if(((add(i, j) != add(j, i))) || (add(i, j) != (i + j)))
				cout << "ERROR: " << i << ", " << j << endl;
		}
	}
	cout << "OK" << endl;

	return 0;
}
