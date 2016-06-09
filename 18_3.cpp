// 18.3 Write a method to randomly generate a set of m integers from an array
// of size n. Each element must have equal probability of being chosen.
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <map>
using namespace std;

vector<int> get_m_rand(const vector<int> &a, int m) {
	vector<int> ret(m);
	for(int i = 0; ((i < m) && (i < int(a.size()))); i ++)
		ret[i] = a[i];
	for(int i = m; i < int(a.size()); i ++) {
		int k = rand() % (i + 1);
		if(k < m)
			ret[k] = a[i];
	}
	return ret;
}

int main(void) {
	srand(time(NULL));

	{ // 1
		int arr[] = {3, 4, 5, 6, 7, 8};
		vector<int> a(arr, arr + sizeof(arr) / sizeof(arr[0]));
		vector<int> r = get_m_rand(a, 3);
		for(size_t i = 0; i < r.size(); i ++)
			cout << r[i] << " ";
		cout << endl;
	}

	{ // 2
		cout << endl << "Batch mode" << endl;
		map<int, int> m;
		for(int i = 0; i < 10; i ++)
			m[i] = 0;

		const int N = 10000;

		for(int i = 0; i < N; i ++) {
			int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
			vector<int> a(arr, arr + sizeof(arr) / sizeof(arr[0]));
			vector<int> r = get_m_rand(a, 5);
			for(size_t i = 0; i < r.size(); i ++)
				m[r[i]] ++;
		}

		for(map<int, int>::iterator it = m.begin(); it != m.end(); ++it)
			cout << int(it->first) << ": " << int(it->second) << endl;

	}
	return 0;
}
