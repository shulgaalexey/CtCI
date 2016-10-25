#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main(void) {
	vector<int> a;
	for(int i = 0; i < 10; i ++)
		a.push_back(i);

	const int V = 6; // Search for this value

	map<int, int> m;
	for(size_t i = 0; i < a.size(); i++)
		m[a[i]] = a[i];

	for(size_t i = 0; i < a.size(); i ++)
		if(m.count(V - a[i]) > 0)
			cout << int(V - a[i]) << ", " << a[i] << endl;

	return 0;
}
