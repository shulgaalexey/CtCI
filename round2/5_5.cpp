#include <iostream>
using namespace std;

int main(void) {
	int A = 0b011101;
	int B = 0b01111;
	int cnt = 0;
	for(int i = 0; i < 32; i++) {
		if((A&1) != (B&1))
			cnt ++;
		A >>= 1;
		B >>= 1;
	}
	cout << cnt << endl;
	return 0;
}
