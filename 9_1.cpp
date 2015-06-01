#include <iostream>
#include <map>
#include <stdexcept>
using namespace std;

map<int, int> _m;

int count_ways(const int N) {
	if(N < 0) throw out_of_range("Negative N");
	int c_N = 0;
	if((N >= 0) && (N <= 3)) c_N = _m[N];
	else if(_m.count(N) > 0) c_N = _m[N];
	else {
		const int c_N_1 = (_m.count(N - 1) > 0) ? _m[N - 1] : count_ways(N - 1);
		const int c_N_2 = (_m.count(N - 2) > 0) ? _m[N - 2] : count_ways(N - 2);
		const int c_N_3 = (_m.count(N - 3) > 0) ? _m[N - 3] : count_ways(N - 3);
		c_N = c_N_1 + c_N_2 + c_N_3;
		_m[N] = c_N;
	}
	return c_N;
}

int main(void) {
	_m[0] = 0;
	_m[1] = 1;
	_m[2] = 2;
	_m[3] = 4;

	bool ok = true;
	ok &= count_ways(4) == 7;
	ok &= count_ways(5) == 13;
	if(!ok) cout << "ERROR!" << endl;
	return 0;
}
