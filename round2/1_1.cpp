#include <iostream>
#include <string.h> // for testing
using namespace std;

bool all_unique(const char *str, const int len) {
	if(len > 26)
		return false; // If using only abc...z,
			// the length of all unique str can not be more
			// than 26 symbols.

	int ex[26] = {0}; // For this purpose may also be used bit mask,
			// made of 32 bit integer

	for(int i = 0; i < len; i ++) {
		if(ex[str[i] - 'a'])
			return false;
		ex[str[i] - 'a'] = 1;
	}


	return true;
}

int main(void) {
	{ // 1
		const char *str = "abcde";
		if(!all_unique(str, strlen(str)))
			cout << "Error1" << endl;
	}

	{ // 2
		const char *str = "abccde";
		if(all_unique(str, strlen(str)))
			cout << "Error2" << endl;
	}

	return 0;
}
