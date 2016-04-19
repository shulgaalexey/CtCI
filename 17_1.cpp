// 17.1 Write a function to swap a number in place (that is, without temporary variables).
#include <iostream>
using namespace std;

void swap_sum(int &a, int &b) {
	b = b + a;
	a = b - a;
	b = b - a;
}

void swap_dif(int &a, int &b) {
	a = a - b;
	b = b + a;
	a = b - a;
}

int main(void) {

	{ // sum
		int a = 3;
		int b = 5;

		swap_sum(a, b);
		if((a != 5) || (b != 3))
			cout << "ERROR sum" << endl;
	}

	{ // dif
		int a = 3;
		int b = 5;

		swap_dif(a, b);
		if((a != 5) || (b != 3))
			cout << "ERROR dif" << endl;
	}

	return 0;
}
