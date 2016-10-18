#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

int N = 3;

vector<string> print(int n) {
	vector<string> v;
	if(n == 0) {
		return v;
	} else if(n == 1) {
		v.push_back("()");
	} else {
		vector<string> deep = print(n - 1);
		for(size_t i = 0; i < deep.size(); i ++) {
			v.push_back("()" + deep[i]);
			v.push_back("(" + deep[i] + ")");
		}

		if(n == N) {
			for(size_t i = 0; i < v.size(); i ++)
				cout << v[i] << endl;
		}
	}
	return v;
}

int main(void) {
	print(3);
	return 0;
}
