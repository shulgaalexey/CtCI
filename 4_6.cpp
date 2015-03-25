// 4.6 Write an algorithm to find the 'next' node (i.e., in-order successor) of a given node
// in a binary search tree. You may assume that each node has a link to its parent.
#include <iostream>
using namespace std;

class node {
	public:
		char value;
		node *left;
		node *right;
		node *parent;
	public:
		node(char v) : value(v), left(NULL), right(NULL), parent(NULL) {}
		node *grand_parent() const {
			if(!parent) return NULL;
			return parent->parent;
		}
		bool is_left() const {
			if(!parent) return false;
			return (this == parent->left);
		}
		bool is_right() const {
			if(!parent) return false;
			return (this == parent->right);
		}
		void set_children(node *l, node *r) {
			left = l;
			right = r;
			if(l) l->parent = this;
			if(r) r->parent = this;
		}
};

node *get_right(node *n, bool prev_left) {
	if(!n) return NULL;
	if(prev_left) {
		if(n->right) return n->right;
		else return get_right(n->parent, n->is_left());
	} else {
		return get_right(n->parent, n->is_left());
	}

}

node *get_next(node *n) {
	if(!n) return NULL;
	if(n->left) return n->left;
	return get_right(n->parent, n->is_left());
}

int main(void) {
	const int N = 12;
	node *n[N] = { 0 };
	for(int i = 0; i < N; i ++) n[i] = new node(char(i));

	// a ----------------------------------------------
	//
	//     1
	//    0 2
	//
	n[1]->set_children(n[0], n[2]);
	bool ok = get_next(n[0]) == n[2];
	ok &= get_next(n[1]) == n[0];
	ok &= get_next(n[2]) == NULL;

	// b ----------------------------------------------
	//
	//       3
	//     1   4
	//    0 2
	//
	n[3]->set_children(n[1], n[4]);
	ok &= get_next(n[0]) == n[2];
	ok &= get_next(n[2]) == n[4];

	// c ----------------------------------------------
	//
	//           4
	//        3     5
	//     1
	//    0 2
	//
	n[3]->set_children(n[1], NULL);
	n[4]->set_children(n[3], n[5]);
	ok &= get_next(n[0]) == n[2];
	ok &= get_next(n[2]) == n[5];

	// d ----------------------------------------------
	//
	//               6
	//        3            10
	//     1     5      8     11
	//    0 2   4      7 9
	//
	n[3]->set_children(n[1], n[5]);
	n[5]->set_children(n[4], NULL);
	n[4]->set_children(NULL, NULL);
	n[6]->set_children(n[3], n[10]);
	n[10]->set_children(n[8], n[11]);
	n[8]->set_children(n[7], n[9]);

	ok &= get_next(n[0]) == n[2];
	ok &= get_next(n[1]) == n[0];
	ok &= get_next(n[2]) == n[5];
	ok &= get_next(n[3]) == n[1];
	ok &= get_next(n[4]) == n[10];
	ok &= get_next(n[5]) == n[4];
	ok &= get_next(n[6]) == n[3];
	ok &= get_next(n[7]) == n[9];
	ok &= get_next(n[8]) == n[7];
	ok &= get_next(n[9]) == n[11]; // !!
	ok &= get_next(n[10]) == n[8];
	ok &= get_next(n[11]) == NULL;

	if(!ok) cout << "PROBLEM!" << endl;
	for(int i = 0; i < N; i ++) delete n[i];
	return 0;
}
