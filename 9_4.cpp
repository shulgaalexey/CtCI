// 9.4 Write a methodto return all subsets of a set
#include <iostream>
#include <set>
#include <map>
#include <string>
using namespace std;

string get_string(const set<char> &s) {
	string str;
	for(set<char>::const_iterator it = s.begin(); it != s.end(); ++it)
		str += *it;
	return str;
}

map<string, set<set<char> > > _m;

set<set<char> > get_subsets(set<char> &s) {
	const string str = get_string(s);
	if(_m.count(str) > 0)
		return _m[str];

	set<set<char> > subs;
	for(set<char>::iterator main_it = s.begin(); main_it != s.end(); ++main_it) {
		const char c = *main_it;
		s.erase(main_it);
		set<char> subs1;
		subs1.insert(c);
		set<set<char> > subs2 = get_subsets(s);
		for(set<set<char> >::iterator it = subs2.begin(); it != subs2.end(); ++it) {
			set<char> cur = *it;
			cur.insert(c);
			subs.insert(cur);
		}
		subs.insert(subs1);
		s.insert(s.end(), c);
	}
	_m[str] = subs;
	return subs;
}


int main(void) {
	char test_data[] = {'1', '3', '2', '7', '6', '5'};
	set<char> s(test_data, test_data + 4);
	set<set<char> > subs = get_subsets(s);
	for(set<set<char> >::iterator it = subs.begin(); it != subs.end(); ++it) {
		set<char> cur = *it;
		cout << get_string(cur) << endl;
	}
	return 0;
}
