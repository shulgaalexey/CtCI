#include <iostream>
using namespace std;

void compress(char *str, const int len) {
	char buf[len + 1] = {0};
	char *end = str + len;
	int cnt = 0;
	int total = 0;
	char *p = str;
	char *push_p = buf;
	while(p < end) {
		if(*p == *(p + 1)) {
			cnt ++;
		} else {
			total += 2;
			if(total >= len) {
				return; // compressed string seems longer
					// than the initial one
			}

			*push_p ++ = *p;
			*push_p ++ = '1' + cnt; // it should be improved
			cnt = 0;
		}
		p ++;
	}

	// Copy the compressed string to the initial one
	p = str;
	push_p = buf;
	while(*push_p)
		*p ++ = *push_p ++;
	*p = 0;
}

int main(void) {
	char str[] = {
		'a',
		'a',
		'b',
		'c',
		'c',
		'c',
		'c',
		'c',
		'a',
		'a',
		'a',
		0
	};

	cout << str << endl;
	compress(str, 11);
	cout << str << endl;

	return 0;
}
