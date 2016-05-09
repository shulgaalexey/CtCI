// 17.4 Write a method which finds the maximum of two numbers.
// You should not use if-else or any other comparison operator.
#include <iostream>
using namespace std;

typedef int(*func_type)(int a, int b);

int sign(unsigned int n) { // 1 - negative, 0 - positive
	return (n >> (sizeof(n) * 8 - 1));
}

int invert_sign(int s) {
	static int inv[] = {1, 0};
	return inv[s];
}

int selecta(int a, int b) {
	return a;
}

int selectb(int a, int b) {
	return b;
}

func_type sel_max[] = {selecta, selectb};

int non_overflow(int a, int b) {
	return sel_max[sign(a - b)](a, b);
}

int overflow(int a, int b) {
	return a * invert_sign(sign(a)) + b * invert_sign(sign(b));
}

func_type sel_algorithm[] = {
	non_overflow,
	overflow,
	overflow,
	non_overflow};

int max(int a, int b) {
	int sa = sign(a);
	int sb = sign(b);
	return sel_algorithm[sa | (sb << 1)](a, b);
}

int main(void) {
	{ //test case 1
		if(max(1, 2) != 2)
			cout << "ERROR1" << endl;
	}

	{ //test case 2
		if(max(2, 1) != 2)
			cout << "ERROR2" << endl;
	}

	{ //test case 3
		if(max(-1, 1) != 1)
			cout << "ERROR3" << endl;
	}

	{ //test case 4
		if(max(1, -1) != 1)
			cout << "ERROR4" << endl;
	}

	{ //test case 5
		if(max(-4000000, 4000000) != 4000000)
			cout << "ERROR5" << endl;
	}

	{ //test case 6
		if(max(3000000, 4000000) != 4000000)
			cout << "ERROR6" << endl;
	}

	cout << "OK" << endl;

	return 0;
}
