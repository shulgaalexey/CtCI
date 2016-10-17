#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

vector<bool> sieve;

int get_next_prime(int prime) {
	int next = prime + 1;

	while(next < int(sieve.size()) && !sieve[next])
		next ++;

	return next;
}

void gen_sieve(int max) {
	sieve.resize(max + 1);

	for(int i = 0; i < max; i ++)
		sieve[i] = true;

	sieve[0] = false;

	int prime = 2;
	while(prime <= sqrt(max)) {
		for(int i = (prime * prime); i < int(sieve.size()); i += prime)
			sieve[i] = false;

		prime = get_next_prime(prime);
	}
}

int main(void) {
	gen_sieve(20);

	for(size_t i = 0; i < sieve.size(); i ++) {
		if(!sieve[i])
			continue;
		cout << i << endl;
	}

	return 0;
}
