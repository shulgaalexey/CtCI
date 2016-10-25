#include <iostream>
using namespace std;

int index(char c) {
	switch(c) {
		case 'R': return 0;
		case 'Y': return 1;
		case 'G': return 2;
		case 'B': return 3;
		default: return -1;
	}
}

void get_hit(const char *a, const char *b, int *h, int *ph) {
	*h = 0;
	*ph = 0;
	int pha[4] = {0};
	int phb[4] = {0};
	for(int i = 0; i < 4; i ++) {
		if(a[i] == b[i]) {
			(*h) ++;
		} else {
			pha[index(a[i])] ++;
			phb[index(b[i])] ++;
		}
	}

	for(int i = 0; i < 4; i ++)
		(*ph) += min(pha[i], phb[i]);
}

int main(void) {
	int h = 0;
	int ph = 0;
	get_hit("RGBY", "GGRR", &h, &ph);
	cout << h << ", " << ph << endl;

	get_hit("RGBY", "GGBR", &h, &ph);
	cout << h << ", " << ph << endl;
	return 0;
}
