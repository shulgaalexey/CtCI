// 17.3 Write an algorithm which computes the number of trailing zeros in n factorial.
#include <iostream>
using namespace std;


int solution(int n) {
	if(n < 0)
		return 0;
	int cnt = 0;
	for(int i = 5; (n / i) > 0; i *= 5)
		cnt += n / i;
	return cnt;
}

int solution2(int n) {
	if(n < 5)
		return 0;

	int last = 2; // for n = 5, last meaning non-zero digit is 2
	int cnt = 1;  // and zero count is 1
	for(int i = 6; i <=  n; i ++) {
		cout << "i = " << i << ", last = " << last << endl;
		last *= i;
		while((last % 10) == 0) {
			last /= 10;
			cnt ++;
		}
		last %= 10;
	}
	return cnt;
}

int main(void) {
	{
		solution(25);
	}

	int ns[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 15, 20, 24, 25, 26, 30, 35};
	int zs[] = {0, 0, 0, 0, 0, 1, 1, 1, 1, 1,  2,  3,  4,  4,  6,  6,  7,  8};

	for(int i = 0; i < int(sizeof(ns) / sizeof(ns[0])); i ++) {
		int r = solution(ns[i]);
		cout << "n = " << ns[i] << ", cnt = " << r << ", expected: " << zs[i];
		if(r != zs[i])
			cout << "  <--- ERROR";
		cout << endl;
	}

	return 0;
}
