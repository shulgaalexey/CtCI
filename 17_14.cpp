// 17.4
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <locale>
using namespace std;

map<string, string> D;

void ADD(const string &s) {
	D[s] = s;
}

void find_word(string &s, string &known, string &unknown) {
	if(s.empty())
		return;

	int word_end = -1;
	int word_begin = -1;
	bool fix_p1 = false;

	for(int p1 = 0; p1 < int(s.length()); p1 ++) {
		word_begin = p1;
		for(int p2 = p1; p2 < int(s.length()); p2 ++) {
			string candidate = s.substr(p1, p2 - p1 + 1);
			if(D.count(candidate) > 0) {
				word_end = p2;
				fix_p1 = true;
				known = candidate;
			}
		}
		if(fix_p1) {
			if(word_begin > 0)
				unknown = s.substr(0, word_begin);
			s.erase(0, word_end + 1);
			return;
		}
	}
	unknown = s;
	s.clear();
}

vector<string> unconcatenate(string s) {
	vector<string> ret;
	while(!s.empty()) {
		string known, unknown;
		find_word(s, known, unknown);
		if(!unknown.empty()) {
			locale loc;
			string UNKNOWN;
			for(string::size_type i = 0; i < unknown.length(); ++i)
				UNKNOWN += toupper(unknown[i],loc);
			ret.push_back(UNKNOWN);
		}
		if(!known.empty())
			ret.push_back(known);
	}
	return ret;
}

int main(void) {
	{ //1
		ADD("look");
		ADD("looked");
		ADD("just");
		ADD("justice");
		ADD("like");
		ADD("line");
		ADD("brot");
		ADD("brother");
		ADD("her");
		ADD("his");

		string s = "jesslookedjustliketimherbrother";
		vector<string> uncat = unconcatenate(s);
		for(size_t i = 0; i < uncat.size(); i ++)
			cout << uncat[i] << " ";
		cout << endl;
	}

	{ //2
		ADD("i");
		ADD("reset");
		ADD("the");
		ADD("computer");
		ADD("it");
		ADD("still");
		ADD("didnt");
		ADD("boot");

		string s = "iresetthecomputeritstilldidntboot";
		vector<string> uncat = unconcatenate(s);
		for(size_t i = 0; i < uncat.size(); i ++)
			cout << uncat[i] << " ";
		cout << endl;
	}

	return 0;
}
