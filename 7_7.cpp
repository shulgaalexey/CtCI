// 7.7 Design an algorithm to find the kth number such that the only prime
// factors are 3, 5 and 7.
#include <iostream>
#include <queue>
#include <stdexcept>
#include <vector>
#include <map>
#include <algorithm>
#include <math.h>
#include <climits>
using namespace std;


// Book approach
int get_prime_book(int k) {
	if(k == 1) return (3 * 5 * 7);
	vector<int> v3;
	vector<int> v5;
	vector<int> v7;
	map<int, int> m;
	v3.push_back(3*5*7);
	m[3*5*7] = 3*5*7;
	int min = INT_MAX;
	for(int i = 0; i < k; i ++) {
		int min_pool = -1;
		min = INT_MAX;
		if(!v3.empty() && (min > v3[0])) {
			min_pool = 3;
			min = v3[0];
		}
		if(!v5.empty() && (min > v5[0])) {
			min_pool = 5;
			min = v5[0];
		}
		if(!v7.empty() && (min > v7[0])) {
			min_pool = 7;
			min = v7[0];
		}
		if(i == (k-1)) break;

		switch(min_pool) {
			case 3: v3.erase(v3.begin()); break;
			case 5: v5.erase(v5.begin()); break;
			case 7: v7.erase(v7.begin()); break;
			default: break;
		}
		m.erase(min);

		int add3 = min * 3;
		if(m.count(add3) == 0) {
			v3.push_back(add3);
			m[add3] = add3;
		}
		int add5 = min * 5;
		if(m.count(add5) == 0) {
			v5.push_back(add5);
			m[add5] = add5;
		}
		int add7 = min * 7;
		if(m.count(add7) == 0) {
			v7.push_back(add7);
			m[add7] = add7;
		}
	}
	return min;
}

// Brute Forcr approach
//
// Idea: add all values to the array, sort it and return the value under kth
// index
vector<int> v;
map<int, int> m;
int get_prime_brute_force(int k) {
	if(v.empty()) {
		for(int a = 1; a < 12; a ++) {
			for(int b = 1; b < 12; b ++) {
				for(int c = 1; c < 12; c ++) {
					const int p = pow(3, a) * pow(5, b) * pow(7, c);
					if(m.count(p) <= 0) {
						m[p] = p;
						v.push_back(p);
					}
				}
			}
		}
		std::sort(v.begin(), v.end());
	}
	if(k >= int(v.size())) return 0;
	return v[k];
}

// Test
int main(void) {
	int k = 1;
	while(k < 100) {
		const int p1 = get_prime_brute_force(k);
		if(p1 == 0) break; // Exceeded the pool of allowed primes
		const int p2 = get_prime_book(k);
		cout << k << " : " << p1 << " : " << p2;
		if(p1 != p2) {
			cout << " : ERROR!";
		}
		cout << endl;
		k ++;
	}
	return 0;
}
