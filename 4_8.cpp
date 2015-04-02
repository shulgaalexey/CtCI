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

static char first_v = 'A';

void reset_labels() {
	first_v = 'A';
}

class node {
	public:
		char value;
		node *left;
		node *right;
	public:
		node() : value(0), left(NULL), right(NULL) {
			value = first_v ++;
			if(first_v > 'Z') reset_labels();
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
	if(!T1 && !T2) return true; // Both trees are finished simultaneously: OK
	if(!T2) return false;
	if(!T1) return false;

	if(T1->value != T2->value) return false;
	return perform_is_subtree_dfs(T1->left, T2->left) && perform_is_subtree_dfs(T1->right, T2->right);
}

bool is_subtree_dfs(node *T1, node *T2) {
	if(!T1 && !T2) return true;
	if(!T1 || !T2) return false;
	if(T1->value == T2->value) {
		if(perform_is_subtree_dfs(T1, T2)) return true;
	}
	if(is_subtree_dfs(T1->left, T2)) return true;
	if(is_subtree_dfs(T1->right, T2)) return true;
	return false;
}

/////////////////////////////////////////////////////////////////////////////
// Books approach, DFS
bool is_subtree_dfs_book(node *r1, node *r2);

bool match_tree_book(node *r1, node *r2);

bool contains_tree_book(node *t1, node *t2) {
	if(!t2) return true; // The empty tree is always a subtree
	return is_subtree_dfs_book(t1, t2);
}

bool is_subtree_dfs_book(node *r1, node *r2) {
	if(!r1) return false; // big tree empty & subtree still not found.
	if(r1->value == r2->value)
		if(match_tree_book(r1, r2)) return true;
	return (is_subtree_dfs_book(r1->left, r2) || is_subtree_dfs_book(r1->right, r2));
}

bool match_tree_book(node *r1, node *r2) {
	if(!r2 && !r1) // if both are empty
		return true; // nothing left in the subtree

	// if one, but not both, are empty
	if(!r1 || !r2) return false;

	if(r1->value != r2->value)
		return false; // data doesn't match
	return (match_tree_book(r1->left, r2->left) && match_tree_book(r1->right, r2->right));
}

/////////////////////////////////////////////////////////////////////////////
string tree2string_preorder(node *tree) {
	if(!tree) return "";
	return string() + tree->value + tree2string_preorder(tree->left) + tree2string_preorder(tree->right);
}

string tree2string_inorder(node *tree) {
	if(!tree) return "";
	return tree2string_inorder(tree->left) + tree->value + tree2string_inorder(tree->right);
}

/////////////////////////////////////////////////////////////////////////////
// Approach: Get two strings S1 and S2 by in-order traversal of T1 and T2
// Find T2 as a substring of T1
bool is_substring(const string &S1, const string &S2) {
	int limit = int(S1.length()) - int(S2.length());
	limit = max(0, limit);
	for(size_t i = 0; i <= size_t(limit); i ++) {
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

bool is_subtree_strings(node *T1, node *T2) {
	return is_substring(tree2string_preorder(T1), tree2string_preorder(T2))
		&& is_substring(tree2string_inorder(T1), tree2string_inorder(T2));

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
		string get_buffer() const {
			string str;
			// may be optimized obviously
			for(size_t i = cur_pos; i < N; i ++) str += buf[i];
			for(size_t i = 0; i < cur_pos; i ++) str += buf[i];
			return str;
		}
		char get_first() const { return buf[cur_pos]; }
};


class krrh {
	private:
		const size_t a;	// alphabet size
		const size_t p;	// prime number
		const size_t N;	// Window size (size of the smaller tree in the task)
		size_t first_base;	// Multiplier of the first digit in the cache

		unsigned long long hash;
		int cur_size;
		circular_buffer str;

	public:
		krrh(const size_t size)
			: a(101)
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
			if(full())
				hash = p + hash - (first_base * get_first()) % p;
			hash = (hash * a + c) % p;
			str.append(c);
			cur_size = min(cur_size + 1, int(N));
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

bool perform_is_subtree_krrh_preorder(node *tree, long long hash, const string &str, krrh &hash_obj) {
	if(!tree) return false;

	hash_obj.append(tree->value);

	if(hash_obj.full())
		if(hash_obj.get_hash() == hash)
			if(hash_obj.get_str() == str)
				return true;

	if(perform_is_subtree_krrh_preorder(tree->left, hash, str, hash_obj)) return true;
	if(perform_is_subtree_krrh_preorder(tree->right, hash, str, hash_obj)) return true;
	return false;
}

bool perform_is_subtree_krrh_inorder(node *tree, long long hash, const string &str, krrh &hash_obj) {
	if(!tree) return false;
	if(perform_is_subtree_krrh_inorder(tree->left, hash, str, hash_obj)) return true;

	hash_obj.append(tree->value);

	if(hash_obj.full())
		if(hash_obj.get_hash() == hash)
			if(hash_obj.get_str() == str)
				return true;
	if(perform_is_subtree_krrh_inorder(tree->right, hash, str, hash_obj)) return true;
	return false;
}

bool is_subtree_krrh_preorder(node *t1, node *t2) {
	const string str= tree2string_preorder(t2); // smaller tree
	const long long hash= get_string_hash(str);
	krrh hash_obj(str.size());
	return perform_is_subtree_krrh_preorder(t1, hash, str, hash_obj);
}
bool is_subtree_krrh_inorder(node *t1, node *t2) {
	const string str= tree2string_inorder(t2); // smaller tree
	const long long hash= get_string_hash(str);
	krrh hash_obj(str.size());
	return perform_is_subtree_krrh_inorder(t1, hash, str, hash_obj);
}

bool is_subtree_krrh(node *t1, node *t2) {
	return is_subtree_krrh_preorder(t1, t2) && is_subtree_krrh_inorder(t1, t2);
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

	{ // Test 1 positive
		reset_labels();

		node *tree = gen_tree(new node(), 3);
		//print_tree(tree);
		//print_tree(gc[9]);

		if(!is_subtree_dfs(tree, gc[9])) cout << "PROBLEM!" << endl;
		if(!is_subtree_dfs_book(tree, gc[9])) cout << "PROBLEM!" << endl;
		if(!is_subtree_strings(tree, gc[9])) cout << "PROBLEM!" << endl;
		if(!is_subtree_krrh(tree, gc[9])) cout << "PROBLEM!" << endl;
		release_gc();
	}

	{ // Test 2 positive
		reset_labels();

		node *tree = gen_tree(new node(), 5);
		//print_tree(tree);
		//print_tree(gc[5]);

		if(!is_subtree_dfs_book(tree, gc[5])) cout << "PROBLEM!" << endl;
		if(!is_subtree_dfs(tree, gc[5])) cout << "PROBLEM!" << endl;
		if(!is_subtree_strings(tree, gc[5])) cout << "PROBLEM!" << endl;
		if(!is_subtree_krrh(tree, gc[5])) cout << "PROBLEM!" << endl;
		release_gc();
	}

	{ // Test 3 positive
		reset_labels();

		node *tree = gen_tree(new node(), 5);
		//print_tree(tree);
		//print_tree(gc[6]);

		if(!is_subtree_dfs_book(tree, gc[6])) cout << "PROBLEM!" << endl;
		if(!is_subtree_dfs(tree, gc[6])) cout << "PROBLEM!" << endl;
		if(!is_subtree_strings(tree, gc[6])) cout << "PROBLEM!" << endl;
		if(!is_subtree_krrh(tree, gc[6])) cout << "PROBLEM!" << endl;
		release_gc();
	}

	{ // Test 4 positive
		reset_labels();

		node *tree = gen_tree(new node(), 5);
		//print_tree(tree);

		node *T = new node('T');
		node *V = new node('V');
		node *W = new node('W');
		node *X = new node('X');
		node *Y = new node('Y');
		node *Z = new node('Z');
		node *A = new node('A');

		T->left = V;
		T->right = W;
		V->left = X;
		V->right = Y;
		W->left = Z;
		W->right = A;

		//print_tree(T);

		if(!is_subtree_dfs(tree, T)) cout << "PROBLEM!" << endl;
		if(!is_subtree_strings(tree, T)) cout << "PROBLEM!" << endl;
		if(!is_subtree_krrh(tree, T)) cout << "PROBLEM!" << endl;
		release_gc();
	}

	{ // Test 5 positive
		reset_labels();

		node *tree = gen_tree(new node(), 5);
		//print_tree(tree);

		node *T = new node('T');
		node *V = new node('V');
		node *W = new node('W');
		node *X = new node('X');
		node *Y = new node('Y');
		node *Z = new node('Z');

		T->left = V;
		T->right = W;
		V->left = X;
		V->right = Y;
		W->left = Z;

		//print_tree(T);

		//if(!is_subtree_dfs(tree, T)) cout << "PROBLEM!" << endl;
		if(!is_subtree_strings(tree, T)) cout << "PROBLEM!" << endl;
		if(!is_subtree_krrh(tree, T)) cout << "PROBLEM!" << endl;
		release_gc();
	}


	{ // Test 6 positive
		reset_labels();

		node *tree = gen_tree(new node(), 5);
		//print_tree(tree);

		node *Y = new node('Y');
		node *F = new node('F');
		node *G = new node('G');
		node *H = new node('H');
		node *I = new node('I');
		node *J = new node('J');
		node *K = new node('K');

		Y->left = F;
		Y->right = G;
		F->left = H;
		F->right = I;
		G->left = J;
		G->right = K;

		//print_tree(Y);

		if(!is_subtree_dfs_book(tree, Y)) cout << "PROBLEM!" << endl;
		if(!is_subtree_dfs(tree, Y)) cout << "PROBLEM!" << endl;
		if(!is_subtree_strings(tree, Y)) cout << "PROBLEM!" << endl;
		if(!is_subtree_krrh(tree, Y)) cout << "PROBLEM!" << endl;
		release_gc();
	}


	{ // Test 7 negative
		node *tree = gen_tree(new node(), 3);

		if(is_subtree_dfs_book(tree, new node())) cout << "PROBLEM!" << endl;
		if(is_subtree_dfs(tree, new node())) cout << "PROBLEM!" << endl;
		if(is_subtree_strings(tree, new node())) cout << "PROBLEM!" << endl;
		if(is_subtree_krrh(tree, new node())) cout << "PROBLEM!" << endl;

		release_gc();
	}


	{ // Test 8 negative
		reset_labels();

		node *tree = gen_tree(new node(), 5);
		//print_tree(tree);

		node *Y = new node('Y');
		node *F = new node('F');
		node *G = new node('G');
		node *H = new node('H');
		node *I = new node('I');
		node *J = new node('J');
		node *K = new node('J');	// Wrong!!

		Y->left = F;
		Y->right = G;
		F->left = H;
		F->right = I;
		G->left = J;
		G->right = K;

		//print_tree(Y);

		if(is_subtree_dfs_book(tree, Y)) cout << "PROBLEM!" << endl;
		if(is_subtree_dfs(tree, Y)) cout << "PROBLEM!" << endl;
		if(is_subtree_strings(tree, Y)) cout << "PROBLEM!" << endl;
		if(is_subtree_krrh(tree, Y)) cout << "PROBLEM!" << endl;
		release_gc();
	}


	{ // Test 9 negative
		reset_labels();

		node *tree = gen_tree(new node(), 2);
		//print_tree(tree);

		node *C = new node('C');
		node *F = new node('F');
		node *G = new node('X');	// Wrong

		C->left = F;
		C->right = G;

		//print_tree(C);

		if(is_subtree_dfs_book(tree, C)) cout << "PROBLEM!" << endl;
		if(is_subtree_dfs(tree, C)) cout << "PROBLEM!" << endl;
		if(is_subtree_strings(tree, C)) cout << "PROBLEM!" << endl;
		if(is_subtree_krrh(tree, C)) cout << "PROBLEM!" << endl;
		release_gc();
	}


	{ // Test 10 negative
		reset_labels();

		node *tree = gen_tree(new node(), 4);
		//print_tree(tree);

		node *S = new node('S');
		node *Z = new node('Z');
		node *A = new node('A');
		node *B = new node('B');
		node *C = new node('C');
		node *D = new node('D');
		node *E = new node('X');	// Wrong!!

		S->left = Z;
		S->right = A;
		Z->left = B;
		Z->right = C;
		A->left = D;
		A->right = E;

		//print_tree(S);

		if(is_subtree_dfs_book(tree, S)) cout << "PROBLEM!" << endl;
		if(is_subtree_dfs(tree, S)) cout << "PROBLEM!" << endl;
		if(is_subtree_strings(tree, S)) cout << "PROBLEM!" << endl;
		if(is_subtree_krrh(tree, S)) cout << "PROBLEM!" << endl;
		release_gc();
	}


	{ // Test 11 positive
		reset_labels();

		node *tree = gen_tree(new node(), 4);
		//print_tree(tree);

		node *S = new node('S');
		node *Z = new node('Z');
		node *A = new node('A');
		node *B = new node('B');
		node *C = new node('C');
		node *D = new node('D');
		node *E = new node('E');

		S->left = Z;
		S->right = A;
		Z->left = B;
		Z->right = C;
		A->left = D;
		A->right = E;

		//print_tree(S);

		if(!is_subtree_dfs_book(tree, S)) cout << "PROBLEM!" << endl;
		if(!is_subtree_dfs(tree, S)) cout << "PROBLEM!" << endl;
		if(!is_subtree_strings(tree, S)) cout << "PROBLEM!" << endl;
		if(!is_subtree_krrh(tree, S)) cout << "PROBLEM!" << endl;
		release_gc();
	}

	return 0;
}
