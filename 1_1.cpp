// Implement an algorithm to determine if a string has all unique characters.
// What if you cannot use additional data structures

#include <iostream>
#include <string>

using namespace std;

bool solution(const string &str) {
	if(str.length() > 128) return false; // There is only 128 unique ASCII characters

	unsigned char existance[256] = {0};
	for(int i = 0; i < int(str.length()); i ++) {
		const unsigned char c = str[i];
		if(existance[c]) return false;
		existance[c] = 1;
	}
	return true;
}

bool solution_no_additional_datastructures(const string &str) {
	for(int i = 0; i < int(str.length()); i ++) {
		const char c = str[i];
		for(int j = i + 1; j < int(str.length()); j ++) {
			const char d = str[j];
			if(c == d) return false;
		}
	}
	return true;
}

int main() {
	if(!solution("abcd")) cout << "PROBLEM!" << endl;
	if(solution("aabcd")) cout << "PROBLEM!" << endl;
	if(!solution("")) cout << "PROBLEM!" << endl;

	if(!solution_no_additional_datastructures("abcd")) cout << "PROBLEM!" << endl;
	if(solution_no_additional_datastructures("aabcd")) cout << "PROBLEM!" << endl;
	if(!solution_no_additional_datastructures("")) cout << "PROBLEM!" << endl;

	return 0;
}
