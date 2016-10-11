#include <iostream>
#include <string>
using namespace std;

bool isSubstring(const string &s1, const string &s2) {
	return (s2.find(s1) >= 0);
}

bool isRotation(const string &s1, const string &s2) {
	return isSubstring(s1, s2 + s2);
}

int main(void) {
	if(!isRotation("waterbottle", "erbottlewat"))
		cout << "Error" << endl;
	else
		cout << "Ok" << endl;
	return 0;
}
