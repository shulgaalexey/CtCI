// 7.7 Design an algorithm to find the kth number such that the only prime
// factors are 3, 5 and 7.
#include <iostream>
#include <queue>
#include <stdexcept>
#include <vector>
#include <map>
#include <algorithm>
#include <math.h>
using namespace std;

// Tree traversal approach
//
// Idea: the pool of allowed prime numbers includes numbers of form
// 7^c * 5^b * 3*a
// Where a, b, c is in the diapazone [1, 10]
// higher values of a,b,c will include 11, which is prohibited prime
// The pool may be present as a trinary tree where
// - each left child is a root * 3
// - each middle child is a root * 5
// - each right child is a root * 7
// Traversing the tree in BFS mode will enumerate all primes in increasing order
//
// This approach generates numbers in incorrect order
int get_prime_bfs(int k) {
	if(k == 1) return (3 * 5 * 7);
	queue<int> *q = new queue<int>();
	q->push(3 * 5 * 7);
	int i = 1;
	int level = 0;
	int pk = 0;
	int prm[] = {3, 5, 7};
	map<int, int> m;
	bool goto_next_level = true;
	do {
		queue<int> *new_q = new queue<int>();
		while(!q->empty()){
			const int p = q->front();
			q->pop();
			for(int idx = 0; idx < 3; idx ++) {
				const int pi = p * prm[idx];
				if(m.count(pi) > 0) continue;
				new_q->push(pi);
				m[pi] = pi;
				new_q->push(pi);
				i++;
				if(i == k) {
					goto_next_level = false;
					break;
				}
			}
			if(!goto_next_level) break;
		}
		delete q;
		if(goto_next_level) {
			level ++;
			if(level > 10) throw out_of_range("Requestes pk is too high");
			q = new_q;
		} else {
			pk = new_q->back();
			delete new_q;
			break;
		}
	} while(true);
	return pk;
}

// Brute Forcr approach
//
// Idea: add all values to the array, sort it and return the value under kth
// index
vector<int> v;
map<int, int> m;
int get_prime_brute_force(int k) {
	if(v.empty()) {
		for(int a = 1; a < 11; a ++) {
			for(int b = 1; b < 11; b ++) {
				for(int c = 1; c < 11; c ++) {
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
	/*int k = 1;
	while(true) {
		cout << "k: " << k << endl;
		const int p1 = get_prime_brute_force(k);
		if(p1 == 0) break; // Exceeded the pool of allowed primes
		const int p2 = get_prime_bfs(k);
		if(p1 != p2) {
			cout << "ERROR! k=" << k << ": " << p1 << "!=" << p2 << endl;
			break;
		}
		k ++;
	}*/

	int k = 1;
	while(k < 100) {
		const int p1 = get_prime_brute_force(k);
		if(p1 == 0) break; // Exceeded the pool of allowed primes
		const int p2 = get_prime_bfs(k);
		cout << k << " : " << p1 << " : " << p2;
		if(p1 != p2) {
			cout << " : ERROR!";
		}
		cout << endl;
		k ++;
	}
	return 0;
}
