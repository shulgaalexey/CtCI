#include <iostream>
using namespace std;

int count(int N) {
	int cnt = 0;
	if(N < 0)
		return -1;

	for(int i = 5; N / i > 0; i *= 5)
		cnt += N / i;

	return cnt;
}

int main(void) {
	cout << count(19) << endl; // 3
	cout << count(5) << endl; // 1
	return 0;
}
