// Algorithm by Karp-Rabin: finding a substring in another string
//
//
#include <iostream>
#include <math.h> // for trace
#include <algorithm>
#include <stdexcept>

using namespace std;


// Finding approximatelly the prime, bigger than a given number:
// Ex:
// p_smaller = 5! - 4! + 3! - 2! + 1!
// p_bigger =  5! + 4! - 3! + 2! - 1!
//
// http://www.magic-squares.net/primes.htm#Primes from Factorials !
//
// Prime numbers will be needed for Hash Function
class prime_gen {
	public:
		static size_t greater_than(const size_t N) {
			size_t step = 3;
			do {
				size_t p = get_prime(step, true);
				if(p > N) return p;
				p = get_prime(step ++, false);
				if(p > N) return p;
			} while(true);
			return 0; // Should not get there
		}
	private:
		static size_t get_prime(size_t n, bool smaller) {
			long long d = (smaller) ? (-1) : (+1);
			long long p = factorial(n--);
			while(n) {
				p += d * factorial(n--);
				d *= (-1);
			}
			return size_t(p);
		}
		static size_t factorial(size_t n) {
			size_t f = 1;
			while(n) f *= n--;
			return f;
		}
};

// Circular buffer
// It will be useful for Karp-Rabin Rolling Hash
class circular_buffer {
	private:
		const size_t N;
		size_t cur_pos;
		char *buf;
	public:
		circular_buffer(const size_t size) : N(size), cur_pos(0), buf(NULL) {
			buf = new char[N];
			for(size_t i = 0; i < N; i ++) buf[i] = 0; // May be optimized with memset
		}
		~circular_buffer() { delete [] buf; }
		void append(char c) {
			buf[cur_pos] = c;
			cur_pos = (cur_pos + 1) % N;
		}
		// this is useless actually
		string get_buffer() const {
			string str;
			// may be optimized obviously
			for(size_t i = cur_pos; i < N; i ++) str += buf[i];
			for(size_t i = 0; i < cur_pos; i ++) str += buf[i];
			return str;
		}
		char get_first() const { return buf[cur_pos]; }
};

// Karp-Rabin Rolling Hash is a cache of a floating window
// http://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-videos/MIT6_006F11_lec09.pdf
class krrh {
	private:
		const size_t a;	// alphabet size, 255
		const size_t p;	// prime number, bigger than window size
		const size_t N;	// Window size (size of the smaller tree in the task)
		size_t first_base;	// Multiplier of the first digit in the cache

		unsigned long long hash;
		int cur_size;
		circular_buffer str;

	public:
		krrh(const size_t size)
			: a(101) // enough for english alphabet
			  //, p( 72057594037927931ULL)
			  //, p(prime_gen::greater_than(10000))
			  , p(prime_gen::greater_than(1ULL<<40))
			  , N(size)
			  , first_base(0)
			  , hash(0)
			  , cur_size(0)
			  , str(size) {
				  unsigned long long fb = 1;
				  for(size_t i = 0; i < (N - 1); i ++) {
					  fb *= a;
					  if(fb > p) fb %= p;
				  }
				  first_base = fb;
			  }

	public:
		void append(char c) {
			if(full()) {
				// remove first
				unsigned long long fb = 1;
				for(size_t i = 0; i < (N - 1); i ++) fb *= a;
				fb %= p;
				const unsigned long long first = (first_base * get_first()) % p;
				hash = p + hash - first;
			}

			str.append(c);
			cur_size = min(cur_size + 1, int(N));
			hash = (hash * a + c) % p;
		}
		bool full() const { return (size_t(cur_size) == N); }
		long long get_hash() const {
			if(!full()) throw out_of_range("krrh::get_hash hash is not full");
			return hash;
		}
		string get_str() const { return str.get_buffer(); }
		char get_first() const { return str.get_first(); }
	public:
		void trace() const {
			cout << get_str() << " | " << hash;
			if(!full())
				cout << "\t~notready";
			cout << endl;
		}
};


int main(void) {

	{ // Testing KRRH 3
		string s1 = "QWERTYUIOPASDFGHJKLZXCVBNMKLMABCDEFGHIJ";
		krrh h1(10);
		for(size_t i = 0; i < s1.length(); i ++) {
			h1.append(s1[i]);
			h1.trace();
		}

		string s2 = "XYZABCDEFGHIJ";
		krrh h2(10);
		for(size_t i = 0; i < s2.length(); i ++) {
			h2.append(s2[i]);
			h2.trace();
		}

		cout << endl;
		cout << h1.get_str() << ":" << h1.get_hash() << "\t";
		cout << endl;
		cout << h2.get_str() << ":" << h2.get_hash() << "\t";
		cout << endl << endl;

		if(h1.get_hash() != h2.get_hash()) cout << "PROBLEM!" << endl;
	}

	return 0;
}
