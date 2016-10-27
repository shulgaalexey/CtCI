#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;


map<string, bool> D;
map<string, int> L;

bool check(const string &w, int level = 0) {
	if(level && D.count(w))
		return true;

	for(int i = 1; i < (int(w.length()) - 1); i ++) {
		string leftw = w.substr(0, i);
		string rightw = w.substr(i);
		if(check(leftw, level + 1) && check(rightw, level + 1)) {
			L[w] = w.length();
		}
	}
	return false;
}

string get_max_len(const vector<string> &v) {

	for(size_t i = 0; i < v.size(); i ++)
		D[v[i]] = true;

	for(size_t i = 0; i < v.size(); i ++)
		check(v[i]);

	int max_len = -1000000;
	string max_word;
	for(size_t i = 0; i < v.size(); i ++) {
		if(L.count(v[i]) == 0)
			continue;
		if(L[v[i]] > max_len) {
			max_len = L[v[i]];
			max_word = v[i];
		}
	}
	return max_word;
}

int main(void) {
	vector<string> v;
	v.push_back("cat");
	v.push_back("banana");
	v.push_back("dog");
	v.push_back("nana");
	v.push_back("walk");
	v.push_back("walker");
	v.push_back("dogwalker");

	cout << get_max_len(v) << endl;

	return 0;
}
