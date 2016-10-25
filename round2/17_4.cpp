#include <iostream>
using namespace std;

int max(int const a, int const b) {
	int tmp = a - b;
	int args[2] = {a, b};
	return args[(tmp >> 31) & 1];
}

int main(void) {
	cout << max(3, 5) << endl;
	return 0;
}
