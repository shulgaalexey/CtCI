/*
// 1.3 Given two strings, write a method to decide if one is a permutation of the other.

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

bool cmp_func(char a, char b) {
	return a < b;
}

vector<char> str2vector(const string &s) {
	if(s.length() <= 0) return vector<char>();

	const char *p = s.c_str();
	vector<char> v(p, p + s.length());
	std::sort(v.begin(), v.end(), cmp_func);
	return v;
}

bool is_permutation_sort(const string &s1, const string &s2) {
	if(s1.length() != s2.length()) return false;

	const vector<char> v1 = str2vector(s1);
	const vector<char> v2 = str2vector(s2);
	for(int i = 0; i < int(v1.size()); i ++)
		if(v1[i] != v2[i]) return false;
	return true;
}

bool is_permutation_count(const string &s1, const string &s2) {
	if(s1.length() != s2.length()) return false;

	int existance[256] = {0};	// ASCII chars
	for(int i = 0; i < int(s1.length()); i ++)
		existance[(unsigned int)s1[i]] ++;
	for(int i = 0; i < int(s2.length()); i ++)
		if(--existance[(unsigned int)s2[i]] < 0) return false;
	return true;
}

int main() {
	if(!is_permutation_sort("abcd", "abcd")) cout << "PROBLEM!" << endl;
	if(!is_permutation_sort("abcd", "acbd")) cout << "PROBLEM!" << endl;
	if(is_permutation_sort("abcd", "abc")) cout << "PROBLEM!" << endl;
	if(is_permutation_sort("abcd", "abcc")) cout << "PROBLEM!" << endl;
	if(!is_permutation_sort("", "")) cout << "PROBLEM!" << endl;

	if(!is_permutation_count("abcd", "abcd")) cout << "PROBLEM!" << endl;
	if(!is_permutation_count("abcd", "acbd")) cout << "PROBLEM!" << endl;
	if(is_permutation_count("abcd", "abc")) cout << "PROBLEM!" << endl;
	if(is_permutation_count("abcd", "abcc")) cout << "PROBLEM!" << endl;
	if(!is_permutation_count("", "")) cout << "PROBLEM!" << endl;

	return 0;
}
*/
