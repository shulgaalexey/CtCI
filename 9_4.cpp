// 9.4 Write a methodto return all subsets of a set
#include <iostream>
#include <set>
#include <map>
#include <string>
#include <vector>
using namespace std;

string get_string(const set<char> &s) {
	string str;
	for(set<char>::const_iterator it = s.begin(); it != s.end(); ++it)
		str += *it;
	return str;
}

char remove_at(set<char> &s, const size_t idx) {
	set<char>::iterator it = s.begin();
	for(size_t i = 0; i < idx; i ++, ++it);
	const char c = *it;
	s.erase(it);
	return c;
}


map<string, set<set<char> > > _m;

set<set<char> > get_subsets(set<char> s) {
	if(s.empty())
		return set<set<char> >();
	if(s.size() == 1) {
		set<set<char> > subs;
		subs.insert(s);
		return subs;
	}

	const string str = get_string(s);
	if(_m.count(str) > 0)
		return _m[str];

	set<set<char> > subs;
	for(size_t i = 0; i < s.size(); i ++) {
		const char c = remove_at(s, i);
		set<char> subs1;
		subs1.insert(c);
		set<set<char> > subs2 = get_subsets(s);
		for(set<set<char> >::iterator it = subs2.begin(); it != subs2.end(); ++it) {
			set<char> cur = *it;
			cur.insert(c);
			subs.insert(cur);
		}
		subs.insert(subs1);
		s.insert(c);
	}
	_m[str] = subs;
	return subs;
}

set<set<char> > get_subsets_book(set<char> s) {
	const size_t size = s.size();

	size_t count = 1;
	for(size_t i = 0; i < size; i ++) count *= 2;

	vector<char> v;
	for(set<char>::iterator it = s.begin(); it != s.end(); ++it) v.push_back(*it);

	set<set<char> > subs;
	for(size_t i = 1; i < count; i ++) {
		set<char> cur;
		for(size_t bit = 0; bit < size; bit ++) {
			if(i & (1 << bit))
				cur.insert(v[bit]);
		}
		subs.insert(cur);
	}
	return subs;
}

int main(void) {
	char test_data[] = {'1', '3', '2', '7', '6', '5'};
	set<char> s(test_data, test_data + 6);

	/* Empty sets are ignored */

	cout << "Solution 1" << endl;
	set<set<char> > subs = get_subsets(s);
	for(set<set<char> >::iterator it = subs.begin(); it != subs.end(); ++it) {
		set<char> cur = *it;
		cout << get_string(cur) << endl;
	}

	cout << "Solution 2" << endl;
	set<set<char> > subs_book = get_subsets_book(s);
	for(set<set<char> >::iterator it = subs_book.begin(); it != subs_book.end(); ++it) {
		set<char> cur = *it;
		cout << get_string(cur) << endl;
	}

	return 0;
}
