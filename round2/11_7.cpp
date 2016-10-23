#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool my_cmp(pair<int, int> a, pair<int, int> b) {
	return ((a.first < b.first) && (a.second < b.second));
}

int main(void) {
	vector<pair<int, int> > v;
	v.push_back(pair<int, int>(65, 100));
	v.push_back(pair<int, int>(70, 150));
	v.push_back(pair<int, int>(56, 90));
	v.push_back(pair<int, int>(75, 190));
	v.push_back(pair<int, int>(60, 95));
	v.push_back(pair<int, int>(68, 110));

	std::sort(v.begin(), v.end(), my_cmp);

	for(size_t i = 0; i < v.size(); i ++)
		cout << v[i].first << ", " << v[i].second << endl;

	return 0;
}
