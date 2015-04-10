// 5.2 Given a real number between 0 and 1 (e.g., 0.72) that is passed in as a double,
// print the binary representation. If the number cannot be represented accurately in binary
// with at most 32 characters, print "ERROR".
#include <iostream>
#include <string>
#include <math.h>
using namespace std;

void print(double d) {
	string s;
	while(d) {
		d *= 2;
		s += (d >= 1) ? '1' : 0;
		if(s.length() > 32) {
			s = "ERROR";
			break;
		}
		d -= int(d);
	}
	cout << ((s.empty()) ? "0" : s) << endl;
}

int main(void) {
	print(0.5);
	print(0.72);
	print(M_PI);
	print(M_PI / 11);
	return 0;
}
