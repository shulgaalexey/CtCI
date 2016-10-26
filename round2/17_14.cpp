#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

map<string, bool> D; // dictionary
map<int, int> dp;
map<int, vector<int> *> cuts;

int estim(const string &s, int start) {
	if(start >= int(s.length()))
		return 0;

	if(D.count(s.substr(start)) > 0)
		return 0;
	if(dp.count(start) > 0)
		return dp[start];


	int penalty = 1000000;
	int cut_index = 0;
	for(int i = start; i < int(s.length()); i ++) {
		int cur_penalty = 0;
		string w = s.substr(start, i - start + 1);
		if(D.count(w) <= 0)
			cur_penalty = int(w.length());
		cur_penalty += estim(s, i + 1);
		if(cur_penalty <= penalty) {
			penalty = cur_penalty;
			cut_index = i;
		}
		if(penalty == 0)
			break;
	}

	dp[start] = penalty;

	if(cuts.count(start) <= 0)
		cuts[start] = new vector<int>();
	cuts[start]->push_back(cut_index);
	return penalty;
}

int main(void) {
	D["look"] = 1;
	D["looked"] = 1;
	D["just"] = 1;
	D["like"] = 1;
	D["her"] = 1;
	D["brother"] = 1;

	int e = estim("jesslookedjustliketimherbrother", 0);
	//int e = estim("jesslook", 0);
	cout << e << endl;
	return 0;

	/*for(map<int, vector<int> * >::iterator it = cuts.begin();
			it != cuts.end(); ++it) {
		vector<int> *v = it->second;
		for(size_t i = 0; i < v->size(); i ++)
			cout << v->at(i) << " ";
		cout << endl;
	}*/
}
