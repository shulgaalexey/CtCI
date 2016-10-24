#include <iostream>
using namespace std;

void swap1(int &a, int &b) {
	a = a + b;
	b = a - b;
	a = a - b;
}

void swap2(int &a, int &b) {
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
}

int main(void) {
	int a = 3;
	int b = 5;

	swap1(a, b);
	cout << a << ", " << b << endl;

	swap2(a, b);
	cout << a << ", " << b << endl;

	return 0;
}
