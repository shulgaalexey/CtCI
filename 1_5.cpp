// 1.5 Inplement a method to perform basic string compression using the counts
// of repeated characters. For example, the string aabcccccaaa would become a2b1c5a3.
// If the "compressed" string would not vecome smaller than the original string,
// your method should return the original string.
// You can assume the string has only uper and lower case letters (a-z)

#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

string encode_char(char c, int cnt) {
	static char buf[10] = {0};
	sprintf(buf, "%c%d", c, cnt);
	return string(buf);
}

string compress(const string &s) {
	const int N = int(s.length());
	if(N <= 2) return s;

	string compressed;
	char cur = s[0];
	int cnt = 1;
	for(int i = 1; i < N; i ++) {
		const char c = s[i];
		if(c != cur) {
			compressed += encode_char(cur, cnt);
			if(int(compressed.length()) >= N) return s;
			cur = c;
			cnt = 1;
		} else {
			cnt ++;
		}
	}
	compressed += encode_char(cur, cnt);
	if(int(compressed.length()) >= N) return s;
	return compressed;
}

int main() {
	if(compress("aabcccccaaa") != "a2b1c5a3") cout << "PROBLEM!" << endl;
	if(compress("aa") != "aa") cout << "PROBLEM!" << endl;
	if(compress("a") != "a") cout << "PROBLEM!" << endl;
	if(compress("") != "") cout << "PROBLEM!" << endl;
	if(compress("abcd") != "abcd") cout << "PROBLEM!" << endl;
	if(compress("aab") != "aab") cout << "PROBLEM!" << endl;
	if(compress("aabb") != "aabb") cout << "PROBLEM!" << endl;

	return 0;
}
