// 18.4 Write a method to count the number of 2s between 0 and n.
#include <iostream>
#include <math.h>
using namespace std;

int count2sInRangeAtDigit(int number, int d) {
	int powerOf10 = pow(10, d);
	int nextPowerOf10 = powerOf10 * 10;
	int right = number % powerOf10;

	int roundDown = number - number % nextPowerOf10;
	int roundUp = roundDown + nextPowerOf10;

	int digit = (number / powerOf10) % 10;
	if(digit < 2)
		return roundDown / 10;
	else if(digit == 2)
		return roundDown / 10 + right + 1;
	else
		return roundUp / 10;
}

int count2s(int number, int length) {
	int count = 0;
	for(int digit = 0; digit < length; digit ++)
		count += count2sInRangeAtDigit(number, digit);
	return count;
}

int main(void) {
	int count = count2s(25, 2);
	cout << count << endl;
	if(count != 9)
		cout << "ERROR" << endl;
	return 0;
}
