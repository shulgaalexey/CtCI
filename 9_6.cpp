// 9.6 Implement an algorithm to print all valid (e.g., properly opened and
// closed) combinations of n-pairs of parentheses.
// EXAMPLE
// Input: 3
// Output: ((())), (()()), (())(), ()(()), ()()()
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

vector<string> get_combinations(int n) {
	vector<string> cmb;
	if(n == 0) return cmb;
	if(n == 1) {
		cmb.push_back("()");
		return cmb;
	}
	vector<string> prev_cmb = get_combinations(n - 1);
	for(size_t i = 0; i < prev_cmb.size(); i ++) {
		string s = prev_cmb[i];
		cmb.push_back("()" + s);
		cmb.push_back("(" + s + ")");
		cmb.push_back(s + "()");
	}
	return cmb;
}

int main(void) {
	map<string, string> m;
	vector<string> cmb = get_combinations(4);
	for(size_t i = 0; i < cmb.size(); i ++) {
		string s = cmb[i];
		if(m.count(s) <= 0) {
			m[s] = s;
			cout << s << endl;
		}
	}
	return 0;
}
