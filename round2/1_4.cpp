#include <iostream>
using namespace std;

void replace_spaces(char *str, const int len, const int buf_len) {
	char *p = str + len - 1;
	char *push_p = str + buf_len - 1;
	while(p >= str) {
		if(*p != ' ') {
			*push_p -- = *p;
		} else {
			*push_p -- = '0';
			*push_p -- = '2';
			*push_p -- = '%';
		}
		p --;
	}
}

int main(void) {
	char str[] = {
		'M',
		'r',
		' ',
		'J',
		'o',
		'h',
		'n',
		' ',
		'S',
		'm',
		'i',
		't',
		' ',
		' ',
		' ',
		' ',
		0
	};

	cout << str << endl;
	replace_spaces(str, 12, 16);
	cout << str << endl;

	return 0;
}
