// 1.4 Write a method to replace all spaces in a string with '%20'.
// You may assume that the string has sufficient space at the end of the string
// to hold the additional characters, and that you are given the "true" length of the string.
// (Note: if implementing in Java, please use a character array
// so that you can perform this operation in place.)
// EXAMPLE:
//  Input:  "Mr John Smith    ", 13
//  Output: "Mr%20John%20Smith"

#include <iostream>
#include <string.h>

using namespace std;

void replace_spaces(char *str, int true_length) {
	char *end = str;
	while(*end) end ++;
	end --;

	for(char *ptr = str + true_length - 1; ptr != str; ptr --) {
		if(*ptr != ' ') {
			*end -- = *ptr;
		} else {
			*end -- = '0';
			*end -- = '2';
			*end -- = '%';
		}
	}
}

int main() {
	char test[] = "Mr John Smith    ";
	char *str = new char[sizeof(test)];
	strncpy(str, test, sizeof(test));
	replace_spaces(str, 13);
	cout << string(str) << endl;
	if(string(str) != "Mr%20John%20Smith") cout << "PROBLEM!" << endl;
	delete [] str;
	return 0;
}
