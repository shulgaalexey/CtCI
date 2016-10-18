#include <iostream>
#include <vector>
using namespace std;

vector<vector<char> > subsets(vector<char> v) {
	vector<vector<char> > ret;

	if(v.size() == 1) {
		vector<char> c;
		c.push_back(v[0]);
		ret.push_back(c);
	} else {
		for(size_t i = 0; i < v.size(); i ++) {
			vector<char> tmp = v;
			tmp.erase(tmp.begin() + i);
			ret.push_back(tmp);

			vector<vector<char> > cur = subsets(tmp);
			for(size_t j = 0; j < cur.size(); j ++)
				ret.push_back(cur[j]);
		}
	}
	return ret;
}

int main(void) {
	vector<char> v;
	v.push_back('a');
	v.push_back('b');
	v.push_back('c');
	v.push_back('d');
	v.push_back('e');

	vector<vector<char> > ret = subsets(v);
	for(size_t i = 0; i < ret.size(); i ++) {
		for(size_t j = 0; j < ret[i].size(); j ++)
			cout << ret[i][j] << " ";
		cout << endl;
	}
	return 0;
}
