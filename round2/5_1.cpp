#include <iostream>
using namespace std;

int main(void) {
	int N = 0b10000000000;
	int M = 0b10011;
	int i = 2;
	int j = 6;

	int mask = ((-1) << (i + j + 1)) | (~((-1) << i));
	N = (N & mask) | (M << i);


	if(N != 0b10001001100)
		cout << "PROBLEM!" << endl;
	return 0;
}
