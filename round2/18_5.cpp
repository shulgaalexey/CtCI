#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

int main(void) {
	// Input
	vector<string> text;
	text.push_back("aaa");
	text.push_back("bbb");
	text.push_back("ccc");
	text.push_back("ddd");
	text.push_back("eee");
	text.push_back("fff");
	text.push_back("ggg");
	text.push_back("ccc");
	text.push_back("aaa");
	text.push_back("bbb");
	text.push_back("ddd");
	text.push_back("eee");
	const string w1 = "ccc";
	const string w2 = "eee";

	// Pre-process
	map<string, vector<int> *> m; // index
	for(size_t i = 0; i < text.size(); i ++) {
		if(m.count(text[i]) == 0)
			m[text[i]] = new vector<int>();
		m[text[i]]->push_back(i);
	}

	// Find a distance
	vector<int> *v1 = m[w1];
	vector<int> *v2 = m[w2];
	int min_dist = 1000000;
	for(size_t i = 0; i < v1->size(); i ++) {
		int prev_dist = 1000000;
		for(size_t j = 0; j < v2->size(); j ++) {
			int dist = std::abs(v1->at(i) - v2->at(j));
			if(dist >= prev_dist)
				break;
			if(dist < min_dist)
				min_dist = dist;
		}
	}
	min_dist --; // Subtracting one, because distance doesn't include
	// neither w1 nor w2

	cout << min_dist << endl;

	return 0;
}
