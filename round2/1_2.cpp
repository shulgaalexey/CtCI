#include <iostream>
using namespace std;

void reverse(char *str) {
	char *p2 = str;
	while(*p2) {
		p2 ++;
	}
	p2 --;


	char *p1 = str;
	while(p1 < p2) {
		char buf = *p1;
		*p1 = *p2;
		*p2 = buf;
		p1 ++;
		p2 --;
	}
}

int main(void) {
	{ // 1
		char str[] = {'a', 'b', 'c', 'd', 'e', 0};
		cout << str << " -> ";
		reverse(str);
		cout << str << endl;
	}

	{ // 2
		char str[] = {'a', 'b', 'c', 'd', 0};
		cout << str << " -> ";
		reverse(str);
		cout << str << endl;
	}

	return 0;
}
