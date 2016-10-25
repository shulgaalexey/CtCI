#include <iostream>
using namespace std;

int main(void) {
	int a[] = {2, -8, 3, -2, 4, -10};
	const int N = int(sizeof(a) / sizeof(a[0]));

	int glob_max = -1000000;
	int cur_max = 0;
	int i1 = -1;
	int i2 = -1;
	bool renew = true;

	for(int i = 0; i < N; i++) {
		//cur_max = max(cur_max + a[i], 0);
		if((cur_max + a[i]) > 0) {
			if(renew) {
				renew = false;
				i1 = i;
			}
			i2 = i;
			cur_max = cur_max + a[i];
		} else {
			cur_max = 0;
			renew = true;
		}
		glob_max = max(cur_max, glob_max);
	}

	cout << glob_max << endl;
	cout << i1 << "..." << i2 << endl;

	return 0;
}
