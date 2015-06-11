// 9.5 Write a method to compute all permutations of a string of unique
// characters.
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
using namespace std;

vector<string> get_permutations_rec(string s) {
	vector<string> perms;
	if(s.empty()) return perms;
	if(s.length() == 1) {
		perms.push_back(s);
		return perms;
	}
	const char c = s[0];
	s.erase(s.begin());
	vector<string> v = get_permutations_rec(s);
	for(size_t i = 0; i < v.size(); i ++) {
		string cur = v[i];
		for(size_t j = 0; j < cur.length(); j ++) {
			string tmp_str = cur;
			string new_str = tmp_str.insert(j, 1, c);
			perms.push_back(new_str);
		}
		perms.push_back(cur + c); // the final permutation
	}
	return perms;
}

vector<string> get_permutations_q(string s) {
	vector<string> perms;
	if(s.empty()) return perms;
	if(s.length() == 1) {
		perms.push_back(s);
		return perms;
	}
	queue<string> q;
	string first;
	first.append(1,s[0]);
	q.push(first);
	while(!q.empty()) {
		string cur = q.front();
		q.pop();
		if(cur.length() == s.length()) {
			perms.push_back(cur);
			continue; // This is a ready permutation
		}
		char c = s[cur.length()];
		for(size_t j = 0; j < cur.length(); j ++) {
			string tmp_str = cur;
			string new_str = tmp_str.insert(j, 1, c);
			q.push(new_str);
		}
		q.push(cur + c);
	}
	return perms;
}

int main(void) {
	//const string s = "abcde";
	const string s = "abcdefg";
	vector<string> p1 = get_permutations_rec(s);
	vector<string> p2 = get_permutations_q(s);
	if(p1.size() != p2.size()) cout << "ERROR!" << endl;

	//for(size_t i = 0; i < p1.size(); i ++) cout << p1[i] << endl;
	//cout << endl << endl;
	//for(size_t i = 0; i < p2.size(); i ++) cout << p2[i] << endl;

	map<string, bool> m;
	for(size_t i = 0; i < p1.size(); i ++) m[p1[i]] = true;;
	for(size_t i = 0; i < p2.size(); i ++) {
		if(m.count(p2[i]) <= 0) {
			cout << "ERROR!" << endl;
			break;
		}
	}

	return 0;
}
