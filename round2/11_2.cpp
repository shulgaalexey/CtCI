#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string sort_chars(string s) {
	char buf[0xFF] = {0};
	for(size_t i = 0; i < s.length(); i ++)
		buf[int(s[i])] ++;
	string ret = "";
	for(int i = 0; i < 0xFF; i ++) {
		if(!buf[i])
			continue;
		for(int j = 0; j < buf[i]; j ++)
			ret += char(i);
	}
	return ret;
}

void sort(vector<string> &v) {
	map<string, vector<string> *> m;
	for(size_t i = 0; i < v.size(); i ++) {
		const string s = sort_chars(v[i]);
		if(m.count(s) <= 0)
			m[s] = new vector<string>();
		m[s]->push_back(v[i]);
	}


	int idx = 0;
	for(map<string, vector<string> *>::iterator it = m.begin();
			it != m.end(); ++it) {
		vector<string> *p = it->second;
		for(size_t i = 0; i < p->size(); i ++) {
			v[idx ++] = p->at(i);
		}
		delete p;
	}
}
int main(void) {
	vector<string> v;
	v.push_back("abc");
	v.push_back("abcba");
	v.push_back("bcd");
	v.push_back("abcba");
	v.push_back("def");
	v.push_back("aabbc");
	v.push_back("cbbaa");
	sort(v);

	for(size_t i = 0; i < v.size(); i ++)
		cout << v[i] << endl;
	return 0;
}
