// 7.4 Write methods to implement the multiply, substract and divide operations
// for integers. Use only the add operator.
#include <iostream>
using namespace std;

#define min(a,b) ((a>b)?b:a)
#define max(a,b) ((a>b)?a:b)
#define abs(a) ((a>=0)?a:(-a))

// a + b
int add(int a, int b) {
	return a + b;
}

// a * b
int mul(int a, int b) {
	if((a == 0) || (b == 0)) return 0;
	int l = abs(a);
	int m = abs(b);
	int sum = 0;
	int smaller = min(l, m);
	int bigger = max(l, m);
	for(int i = 0; i < smaller; i ++)
		sum = add(sum, bigger);
	if((a >= 0) && (b >= 0))
		return sum;
	if((a < 0) && (b < 0))
		return sum;
	return (-sum);
}

// a - b
int sub(int a, int b) {
	if(b == 0) return a;
	if(a == 0) return (-b);
	if(a == b) return 0;
	int l = max(a, b);
	int m = min(a, b);
	int ret = 0;
	do {
		if(add(ret, m) == l)
			break;
		ret ++;
	} while(true);
	if(a > b) return ret;
	else return (-ret);
}

// a / b
int div(int a, int b) {
	if(a == 0) return 0;
	if(b == 0) {
		cout << "Exception: divizion by zero" << endl;
		return 0;
	}
	if(a == b) return 1;
	int l = abs(a);
	int m = abs(b);
	if(l < m) return 0;
	int ret = 1;
	do {
		if(mul(ret, m) == l)
			break;
		if(mul(ret + 1, m) > l)
			break;
		ret ++;
	} while(true);
	if((a >= 0) && (b >= 0))
		return ret;
	if((a < 0) && (b < 0))
		return ret;
	return (-ret);
}

int main(void) {
	bool ok = true;

	ok &= mul(0, 0) == 0;
	ok &= mul(1, 0) == 0;
	ok &= mul(0, 1) == 0;
	ok &= mul(1, 1) == 1;
	ok &= mul(1, 2) == 2;
	ok &= mul(-1, 2) == (-2);
	ok &= mul(-1, -2) == 2;
	ok &= mul(1, -2) == (-2);

	ok &= sub(0, 0) == 0;
	ok &= sub(1, 0) == 1;
	ok &= sub(0, 1) == (-1);
	ok &= sub(-10, -20) == 10;
	ok &= sub(10, 20) == (-10);

	ok &= div(0, 0) == 0;
	ok &= div(1, 0) == 0;
	ok &= div(1, 1) == 1;
	ok &= div(4, 2) == 2;
	ok &= div(-4, 2) == (-2);
	ok &= div(4, -2) == (-2);
	ok &= div(-4, -2) == 2;
	ok &= div(2, 4) == 0;
	ok &= div(5, 3) == 1;

	if(!ok) cout << "ERROR!" << endl;

	return 0;
}
