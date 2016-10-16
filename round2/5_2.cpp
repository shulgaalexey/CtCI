#include <iostream>
#include <vector>
using namespace std;

int main(void) {
	//double d = 0.72;
	//double d = 0.75;
	double d = 0.71875;
	vector<int> b;
	int coef = 2;
	double base = 1. / coef;
	for(int i = 0; i <= 32; i++) {
		if(d == base) {
			b.push_back(1);
			break;
		} else if(d > base) {
			b.push_back(1);
			d -= base;
		} else
			b.push_back(0);
		coef *= 2;
		base = 1. / coef;
	}

	if(b.size() > 32) {
		cout << "ERROR" << endl;
		for(size_t i = 0; i < b.size(); i ++)
			cout << b[i];
		cout << endl;
	} else {
		for(size_t i = 0; i < b.size(); i ++)
			cout << b[i];
		cout << endl;
	}

	return 0;
}
