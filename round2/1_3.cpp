#include <iostream>
#include <string.h>
using namespace std;

bool is_permutation(const char *s1, const char *s2) {
	if(strlen(s1) != strlen(s2))
		return false;

	int ex1[26] = {0};
	int ex2[26] = {0};

	for(unsigned int i = 0; i < strlen(s1); i ++) {
		ex1[s1[i] - 'a'] ++;
		ex2[s2[i] - 'a'] ++;
	}

	for(int i = 0; i < 26; i ++) {
		if(ex1[i] != ex2[i])
			return false;
	}

	// It may be done with a single array int ex[26]
	// In this case we increment its items while iterating through
	// characters of s1.
	// Than we decrement its items while iterating throught
	// characters of s2.
	// As soon as negative item of ex[] is detected, we are sure
	// that the strings are not permutations

	return true;
}

int main(void) {
	{ // 1
		if(!is_permutation("abcd", "badc"))
			cout << "Error1" << endl;
	}
	{ // 2
		if(!is_permutation("abacada", "baaaadc"))
			cout << "Error2" << endl;
	}
	{ // 3
		if(is_permutation("abcd", "abc"))
			cout << "Error3" << endl;
	}
	{ // 4
		if(is_permutation("abcd", "abce"))
			cout << "Error4" << endl;
	}
	cout << "OK" << endl;
	return 0;
}
