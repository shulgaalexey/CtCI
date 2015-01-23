/*
// 1.8 Assume you have a method isSubstring which checks if one word is a substring of another.
// Given two strings, s1 and s2, write code to check if s2 is a rotation on s1
// using only one call to isSubstring
// (e.g. "waterbottle" is a rotation of erbottlewat")

#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

bool isSubstring(const string &s, const string &bigger_string) {
	//cout << s << ", " << bigger_string << ", " << bigger_string.find(s) << endl;
	return (bigger_string.find(s) != size_t(-1));
}

bool isRotation(const string &s1, const string s2) {
	if(s1.length() != s2.length()) return false;
	return isSubstring(s1, s2 + s2);
}

bool isRotationBF(const string &s1, const string &s2) {
	if(s1.length() != s2.length()) return false;
	string s3 = s2;
	for(size_t i = 0; i < s1.length(); i ++) {
		const char first = s3[0];
		s3.erase(0, 1);
		s3 += first;
		if(s1 == s3) return true;
	}
	return false;
}

string genRandom(const int N) {
	static const char alphanumeric[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
	char *str = new char[N + 1];
	for(int i = 0; i < N; i++)
		str[i] = alphanumeric[rand() % (sizeof(alphanumeric)-1)];
	str[N] = 0;
	const string rnd_str(str);
	delete [] str;
	return rnd_str;
}

string genRotation(const string &s) {
	if(s.length() < 2) return s;
	const int shift = rand() % (s.length() - 1);
	string first = s.substr(0, shift);
	string second= s.substr(shift);
	return second + first;
}

int main() {
	if(!isRotation("waterbottle", "erbottlewat")) cout << "PROBLEM!" << endl;
	if(isRotation("waterbottle", "erbottlewab")) cout << "PROBLEM!" << endl;
	if(!isRotation("abcd", "bcda")) cout << "PROBLEM!" << endl;
	if(!isRotation("abcd", "cdab")) cout << "PROBLEM!" << endl;
	if(!isRotation("abcd", "dabc")) cout << "PROBLEM!" << endl;

	if(!isRotationBF("waterbottle", "erbottlewat")) cout << "PROBLEM!" << endl;
	if(isRotationBF("waterbottle", "erbottlewab")) cout << "PROBLEM!" << endl;
	if(!isRotationBF("abcd", "bcda")) cout << "PROBLEM!" << endl;
	if(!isRotationBF("abcd", "cdab")) cout << "PROBLEM!" << endl;
	if(!isRotationBF("abcd", "dabc")) cout << "PROBLEM!" << endl;

	srand(time(NULL));
	for(int length = 1; length < 10; length ++) {
		for(int test = 0; test < 20000; test ++) {
			const string s1 = genRandom(length);
			const string s2 = genRotation(s1);
			if(!isRotation(s1, s2))
				cout << "PROBLEM!" << s1 << ", " << s2 << " Rotation!" << endl;
			const string s3 = genRandom(length);
			if(isRotation(s1, s3) != isRotationBF(s1, s3))
				cout << "PROBLEM! BF found dif result" << endl;
		}
	}
	return 0;
}
*/
