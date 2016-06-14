// 18.5 You have a large text file containing words. Given any two words, find
// the shortest distance (in terms of words) between them in the file. If the
// operation will be repeated many times for the same file (but different pairs
// of words), can you optimize your solution?

#include <iostream>
#include<string>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

map<string, vector<int> *> _m;

void preprocess(const string &text) {
	istringstream iss(text);
	string word;
	int idx = 0;
	while(iss >> word) {
		// Remove punctuation
		string result;
		std::remove_copy_if(word.begin(), word.end(),
				std::back_inserter(result),
				std::ptr_fun<int, int>(&std::ispunct));
		word = result;

		if(_m.count(word) <= 0)
			_m[word] = new vector<int>();
		_m[word]->push_back(idx++);
	}
}

static bool __pair_sort(pair<char, int> a, pair<char, int> b) {
	return a.second < b.second;
}

int get_distance(const string &w1, const string &w2) {
	if((_m.count(w1) <= 0) || (_m.count(w2) <= 0))
		return -1;

	vector<int> *v1 = _m[w1];
	vector<int> *v2 = _m[w2];

	vector<pair<char, int> > v(v1->size() + v2->size());
	size_t idx = 0;
	for(size_t i = 0; i < v1->size(); i ++)
		v[idx++] = pair<char, int>('a', (*v1)[i]);
	for(size_t i = 0; i < v2->size(); i ++)
		v[idx++] = pair<char, int>('b', (*v2)[i]);

	std::sort(v.begin(), v.end(), __pair_sort);

	int min_dist = 1000000;
	for(size_t i = 1; i < v.size(); i ++) {
		if(v[i - 1].first != v[i].first) {
			const int dist = v[i].second - v[i - 1].second;
			min_dist = min(min_dist, dist);
		}
	}
	return min_dist;
}

int main(void) {
	const string text =
		"Binary function that accepts two elements in the range as "
		"arguments, and returns a value convertible to bool. The value "
		"returned indicates whether the element passed as first argument "
		"is considered to go before the second in the specific strict "
		"weak ordering it defines. "
		"The function shall not modify any of its arguments. "
		"This can either be a function pointer or a function object.";

	preprocess(text);

	cout << "Dictionary index: " << endl;
	for(map<string, vector<int> *>::iterator it = _m.begin(); it != _m.end(); ++it) {
		const string word = it->first;
		cout << word << ": ";
		vector<int> *v = it->second;
		for(size_t i = 0; i < v->size(); i ++)
			cout << int((*v)[i]) << " ";
		cout << endl;
	}
	cout << endl;

	int dist = get_distance("function", "modify");
	cout << "Distance between function and modify is: " << dist << endl;
	if(dist != 3)
		cout << "ERROR" << endl;

	return 0;
}
