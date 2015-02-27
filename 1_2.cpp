// Implement a function void reverse(char *str) in C or C++ which reverses a null-terminated string

#include <iostream>
#include <string.h>

using namespace std;

void reverse(char *str) {
	if(!str) return;

	// find final character ptr
	char *p2 = str;
	while(*p2) p2 ++;
	p2--;

	// reverse the string
	char *p1 = str;
	while(p1 < p2) {
		const char tmp = *p1;
		*p1 ++ = *p2;
		*p2 -- = tmp;
	}
}

int main() {
	{
		const char test[] = "abc";
		char *str = new char[sizeof(test)];
		strncpy(str, test, sizeof(test));
		reverse(str);
		if(string(str) != "cba") cout << "PROBLEM!" << endl;
		delete [] str;
	}

	{
		const char test[] = "abcd";
		char *str = new char[sizeof(test)];
		strncpy(str, test, sizeof(test));
		reverse(str);
		if(string(str) != "dcba") cout << "PROBLEM!" << endl;
		delete [] str;
	}

	{
		char *str = NULL;
		reverse(str);
	}

	{
		const char test[] = "a";
		char *str = new char[sizeof(test)];
		strncpy(str, test, sizeof(test));
		reverse(str);
		if(string(str) != "a") cout << "PROBLEM!" << endl;
		delete [] str;
	}

	{
		const char test[] = "";
		char *str = new char[sizeof(test)];
		strncpy(str, test, sizeof(test));
		reverse(str);
		if(string(str) != "") cout << "PROBLEM!" << endl;
		delete [] str;
	}

	return 0;
}
