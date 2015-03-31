// 4.8 You have a very large binary trees: T1, with millions of nodes, and T2, with hundreds of nodes.
// Create an algorithm to decide if T2 is a subtree of T1.
// A tree T2 is a subtree of  T1 if there exists a node n in T1 such that the subtree of
// n is identical to T2. That is, if you cut off the tree at node n, the two trees would
// be identical.
#include <iostream>
#include <vector>
#include <queue>
#include <math.h> // for trace
#include <iomanip> // for trace
#include <algorithm>
#include <stdexcept>

using namespace std;

vector<class node *> gc;

static char first_v = 'A';//60;//33;

void reset_labels() {
	first_v = 'A';//60;//33;
}

class node {
	public:
		char value;
		node *left;
		node *right;
	public:
		node() : value(0), left(NULL), right(NULL) {
			value = first_v ++;
			if(first_v > 'Z'/*126*/) reset_labels();
			gc.push_back(this);
		}
		node(int v) : value(v), left(NULL), right(NULL) {
			gc.push_back(this);
		}
};

void release_gc() {
	for(size_t i = 0; i < gc.size(); i ++) delete gc[i];
	gc.clear();
}

/////////////////////////////////////////////////////////////////////////////
// DFS approach
bool perform_is_subtree_dfs(node *T1, node *T2) {
	if(!T2) return true;
	if(!T1) return true;
	if(T1->value != T2->value) return false;
	return perform_is_subtree_dfs(T1->left, T2->left) && perform_is_subtree_dfs(T1->right, T2->right);
}

bool is_subtree_dfs(node *T1, node *T2) {
	if(!T1 || !T2) return false;
	if(T1->value == T2->value) {
		if(perform_is_subtree_dfs(T1, T2)) return true;
	}
	if(is_subtree_dfs(T1->left, T2)) return true;
	if(is_subtree_dfs(T1->right, T2)) return true;
	return false;
}

/////////////////////////////////////////////////////////////////////////////
string tree2string(node *tree) {
	if(!tree) return "";
	return tree2string(tree->left) + tree->value + tree2string(tree->right);
}

/////////////////////////////////////////////////////////////////////////////
// Approach: Get two strings S1 and S2 by in-order traversal of T1 and T2
// Find T2 as a substring of T1
bool is_subtree_strings(node *T1, node *T2) {
	const string S1 = tree2string(T1);
	const string S2 = tree2string(T2);

	int limit = int(S1.length()) - int(S2.length());
	limit = max(0, limit);
	for(size_t i = 0; i < size_t(limit); i ++) {
		bool dif = false;
		for(size_t j = 0; j < S2.length(); j ++) {
			size_t idx = j + i;
			if(idx >= S1.length()) return false;
			if(S1[idx] != S2[j]) {
				dif = true;
				break;
			}
		}
		if(!dif) return true;
	}
	return false;
}

/////////////////////////////////////////////////////////////////////////////
// Approach: Use Karp-Rabin Rolling Hash with strings,
// obtained during in-order traversal of trees.
// Once the strings are prepared, the hash of smaller string is
// searched iteratively in the bigger string.
/////////////////////////////////////////////////////////////////////////////

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

		unsigned long long hash;
		int cur_size;
		circular_buffer str;

	public:
		//krrh(const size_t size, const size_t max_size = 10000000)	// T2 is supposed to have 10M nodes
		krrh(const size_t size, const size_t max_size = 101)	// T2 is supposed to have 10M nodes
			  //: a(1<<5) // enough for english alphabet
			  : a(100) // enough for english alphabet
			  //, p(prime_gen::greater_than(max(size, max_size)))
			  , p( 72057594037927931ULL)
			  , N(size)
		      , hash(0)
			  , cur_size(0)
			  , str(size)
	{}
	public:
		void append(char c) {
			str.append(c);
			cur_size = min(cur_size + 1, int(N));
			//hash = ((hash % p) * a + c) % p;
			hash = ((hash * a) % p + c) % p;
		}
		void skip(char c) {
			if(cur_size <= 0) throw out_of_range("krrh::skip negative size");

			size_t first_exp = min(N, size_t(cur_size));
			size_t first_base = 1;
			for(size_t i = 0; i < (first_exp - 1); i ++)
				first_base *= a;

			hash = (hash % p - c * (first_base % p)) %p;
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

long long get_string_hash(const string &str) {
	if(str.empty()) return 0;
	krrh hash_obj(str.size());
	for(size_t i = 0; i < str.size(); i ++) hash_obj.append(str[i]);
	return hash_obj.get_hash();
}

bool perform_is_subtree_krrh(node *tree, long long hash, const string &str, krrh &hash_obj) {
	if(!tree) return false;
	if(perform_is_subtree_krrh(tree->left, hash, str, hash_obj)) return true;

	//cout << "\t\t\t" << tree->value << endl;

	if(!hash_obj.full()) {
		hash_obj.append(tree->value);
	} else {
		const char c = hash_obj.get_first();
		hash_obj.append(tree->value);
		hash_obj.skip(c);
	}

	if(hash_obj.full()) {
		if(hash_obj.get_str() == str) cout << endl;
		cout << hash_obj.get_str() << "\t" << str << "\t" << hash_obj.get_hash() << "\t" << hash << endl;
		if(hash_obj.get_str() == str) {
			cout << get_string_hash(hash_obj.get_str()) << endl << endl;
		}
	}
	//if(hash_obj.full() && (hash_obj.get_hash() == hash) && (hash_obj.get_str() == str)) return true;
	if(hash_obj.full())
		if(hash_obj.get_hash() == hash)
			if(hash_obj.get_str() == str)
				return true;
	if(perform_is_subtree_krrh(tree->right, hash, str, hash_obj)) return true;
	return false;
}

bool is_subtree_krrh(node *t1, node *t2) {
	const string str = tree2string(t2); // smaller tree
	const long long hash = get_string_hash(str);
	krrh hash_obj(str.size());
	return perform_is_subtree_krrh(t1, hash, str, hash_obj);
}

/////////////////////////////////////////////////////////////////////////////﻿

node *gen_tree(node *root, int depth) {
	if(!depth) return NULL;
	root->left = new node();
	root->right = new node();
	gen_tree(root->left, depth - 1);
	gen_tree(root->right, depth - 1);
	return root;
}

// Visualize the tree -------------------------------------
// taken from the internet
size_t get_height(node *tree) {
	if(!tree) return 0;
	return max(get_height(tree->left), get_height(tree->right)) + 1;
}

void print_tree(node *root) {
	const int box_size = 3;
	queue<node *> q;
	q.push(root);
	size_t current_level_nodes = 1;
	size_t next_current_level_nodes = 0;
	size_t level = 1;

	const size_t height = get_height(root);

	int padding = box_size * (pow(2, height - level) - 1);
	cout << setw(padding / 2) << "";
	while (level <= height)
	{
		cout << setw(box_size);
		if (q.front() != NULL)
		{
			cout << q.front()->value;
			q.push(q.front()->left);
			q.push(q.front()->right);
		}
		else
		{
			std::cout << "";
			q.push(NULL);
			q.push(NULL);
		}
		next_current_level_nodes += 2;
		cout << setw(padding) << "";
		q.pop();
		--current_level_nodes;
		if (current_level_nodes == 0)
		{
			current_level_nodes = next_current_level_nodes;
			next_current_level_nodes = 0;
			++level;
			padding = box_size * (pow(2, height - level) - 1);
			cout << "\n" << setw(padding / 2) << "";
		}
	}
	cout << endl << endl;
}


int main(void) {
	{ // Testing KRRH 1
		krrh h1(4, 4*100*100*100*100);
		h1.trace();
		h1.append('A');
		h1.trace();
		h1.append('B');
		h1.trace();
		h1.append('C');
		h1.trace();
		h1.append('D');
		h1.trace();

		krrh h2(4, 4*100*100*100*100);
		h2.trace();
		h2.append('X');
		h2.trace();
		h2.append('A');
		h2.trace();
		h2.append('B');
		h2.trace();
		h2.append('C');
		h2.trace();
		h2.skip('X');
		h2.trace();
		h2.append('D');
		h2.trace();

		cout << h1.get_str() << ":" << h2.get_str() << "\t";
		cout << h1.get_hash() << ":" << h2.get_hash() << endl;
	}

	{ // Testing KRRH 2
		krrh h1(4);
		h1.trace();
		h1.append('A');
		h1.trace();
		h1.append('B');
		h1.trace();
		h1.append('C');
		h1.trace();
		h1.append('D');
		h1.trace();

		krrh h2(4);
		h2.trace();
		h2.append('X');
		h2.trace();
		h2.append('A');
		h2.trace();
		h2.append('B');
		h2.trace();
		h2.append('C');
		h2.trace();
		h2.skip('X');
		h2.trace();
		h2.append('D');
		h2.trace();

		cout << h1.get_str() << ":" << h2.get_str() << "\t";
		cout << h1.get_hash() << ":" << h2.get_hash() << endl;
	}

	{ // Test 1 positive
		reset_labels();

		node *tree = gen_tree(new node(), 3);
		print_tree(tree);
		print_tree(gc[9]);

		if(!is_subtree_dfs(tree, gc[9])) cout << "PROBLEM!" << endl;
		if(!is_subtree_strings(tree, gc[9])) cout << "PROBLEM!" << endl;
		if(!is_subtree_krrh(tree, gc[9])) cout << "PROBLEM!" << endl;
		release_gc();
	}

	{ // Test 2 positive
		reset_labels();

		node *tree = gen_tree(new node(), 5);
		print_tree(tree);
		print_tree(gc[5]);

		if(!is_subtree_dfs(tree, gc[5])) cout << "PROBLEM!" << endl;
		if(!is_subtree_strings(tree, gc[5])) cout << "PROBLEM!" << endl;
		if(!is_subtree_krrh(tree, gc[5])) cout << "PROBLEM!" << endl;
		release_gc();
	}

	{ // Test 3 positive
		reset_labels();

		node *tree = gen_tree(new node(), 5);
		print_tree(tree);
		print_tree(gc[6]);

		if(!is_subtree_dfs(tree, gc[6])) cout << "PROBLEM!" << endl;
		if(!is_subtree_strings(tree, gc[6])) cout << "PROBLEM!" << endl;
		if(!is_subtree_krrh(tree, gc[6])) cout << "PROBLEM!" << endl;
		release_gc();
	}

	{ // Test 4 positive
		reset_labels();

		node *tree = gen_tree(new node(), 5);
		print_tree(tree);

		node *B = new node('B');
		node *I = new node('I');
		node *J = new node('J');
		node *K = new node('K');
		node *L = new node('L');
		node *M = new node('M');
		node *N = new node('N');

		B->left = I;
		B->right = J;
		I->left = K;
		I->right = L;
		J->left = M;
		J->right = N;

		print_tree(B);

		if(!is_subtree_dfs(tree, B)) cout << "PROBLEM!" << endl;
		if(!is_subtree_strings(tree, B)) cout << "PROBLEM!" << endl;
		if(!is_subtree_krrh(tree, B)) cout << "PROBLEM!" << endl;
		release_gc();
	}



	{ // Test 5 negative
		node *tree = gen_tree(new node(), 3);

		if(is_subtree_dfs(tree, new node())) cout << "PROBLEM!" << endl;
		if(is_subtree_strings(tree, new node())) cout << "PROBLEM!" << endl;
		if(is_subtree_krrh(tree, new node())) cout << "PROBLEM!" << endl;

		release_gc();
	}

	return 0;
}
