#include <iostream>
#include <string>
#include <vector>
//#include <map>
using namespace std;


vector<string> perm(string s) {
	if(s.length() == 1) {
		vector<string> v;
		v.push_back(s);
		return v;
	}

	vector<string> ret;
	for(size_t i = 0; i < s.length(); i ++) {
		char c[2] = {0};
		c[0] = s[i];
		string sc = c;
		string tmp = s;
		tmp.erase(i, 1);
		if(tmp.empty())
			continue;
		vector<string> cur_perms = perm(tmp);
		for(size_t j = 0; j < cur_perms.size(); j ++)
			ret.push_back(sc + cur_perms[j]);

	}
	return ret;
}

int main(void) {
	string s = "abcd";
	vector<string> perms = perm(s);

	for(size_t i = 0; i < perms.size(); i ++)
		cout << perms[i] << endl;
/*
	cout << "-------------------" << endl;

	map<string, string> m;
	for(size_t i = 0; i < perms.size(); i ++)
		if(m.count(perms[i]) <= 0)
			m[perms[i]] = perms[i];
	for(map<string, string>::iterator it = m.begin(); it != m.end(); ++it)
		cout << it->first << endl;

	cout << "-------------------" << endl;
	cout << perms.size() << " | " << m.size() << endl;
*/


	return 0;
}
