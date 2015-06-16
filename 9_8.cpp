// 9.8 Given an infinit number of quarters (25 cents), dimes (10 cents), nickels
// (5 cents) and pennies (1 cent),  write code to calculate the number of ways
// representing n cents.
#include <iostream>
#include <set>
#include <string>
#include <map>

using namespace std;

map<int, set<string> > _m;

void trace_set(const string &caption, const set<string> &s) {
	cout << caption << endl;
	for(set<string>::iterator it = s.begin(); it != s.end(); ++it) {
		string str = *it;
		cout << str << endl;
	}
}

void populate_with(const set<string> &in_set, const char c, set<string> &out_set) {
	if(in_set.empty()) return;
	for(set<string>::const_iterator it = in_set.begin(); it != in_set.end(); ++it) {
		string str = *it;
		for(size_t i = 0; i < str.length(); i ++ ) {
			string tmp_str = str;
			tmp_str.insert(i, 1, c);
			out_set.insert(tmp_str);
		}
		str.append(1, c);
		out_set.insert(str);
	}
	//trace_set("combinations for " + c, out_set);
}



set<string> get_combinations(int n) {
	set<string> cmb;
	if(n <= 0) {
		//cmb.insert("");
		return cmb;
	}
	if(n == 1) {
		cmb.insert("p");
		return cmb;
	}
	if(_m.count(n) > 0) return _m[n];
	if(n == 5) cmb.insert("n");
	if(n == 10) cmb.insert("d");
	if(n == 25) cmb.insert("q");

	populate_with(get_combinations(n - 25), 'q', cmb);
	populate_with(get_combinations(n - 10), 'd', cmb);
	populate_with(get_combinations(n - 5), 'n', cmb);
	populate_with(get_combinations(n - 1), 'p', cmb);

	_m[n] = cmb;

	cout << endl << "n = " << n << endl;
	trace_set("combinations", cmb);
	cout << "totally: " << cmb.size() << endl;
	cout << "-------------" << endl;
	return cmb;
}

int get_cmb_number(int n) {
	return get_combinations(n).size();
}

int main(void)  {
	bool ok = true;
	ok &= get_cmb_number(0) == 0;
	ok &= get_cmb_number(1) == 1;
	ok &= get_cmb_number(4) == 1;
	ok &= get_cmb_number(5) == 2;
	ok &= get_cmb_number(6) == 3;
	ok &= get_cmb_number(7) == 4;
	if(!ok) cout << "ERROR!" << endl;

	//for(int i = 8; i < 26; i ++) get_cmb_number(i);
	return 0;
}
