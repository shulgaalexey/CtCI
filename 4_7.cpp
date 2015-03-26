// 4.7 Design an algorithm and write code to find the first common ancestor of two nodes in a binary tree.
// Avoid storing additional nodes in a data structure.
// NOTE: this is not necessarily a binary search tree.
#include <iostream>
using namespace std;

class node {
	public:
		char value;
		node *left;
		node *right;
	public:
		node(char v) : value(v), left(NULL), right(NULL) {}
		void set_children(node *l, node *r) {
			left = l; right = r;
		}
};

// Main idea:
// If previous state was: not all nodes are found deeper the child of the current node
// but the new state is: all nodes are found,
// than we have a first common ancestor
// Also, returning from the recursion we should preserve the found ancestor
node *perform_find_ancestor(node *tree, node *n1, node *n2, bool &b1, bool &b2) {
	if(!tree || !n1 || !n2) return NULL;

	bool prev_b1 = b1, prev_b2 = b2;
	node *ret = perform_find_ancestor(tree->left, n1, n2, b1, b2);
	if(ret) return ret;
	if((b1 && b2) && ((prev_b1!=b1) && (prev_b2!=b2))) return tree;

	ret = perform_find_ancestor(tree->right, n1, n2, b1, b2);
	if(ret) return ret;
	if((b1 && b2) && ((prev_b1!=b1) && (prev_b2!=b2))) return tree;

	if(tree == n1) b1 = true;
	if(tree == n2) b2 = true;
	return NULL;
}

node *find_ancestor(node *tree, node *n1, node *n2) {
	bool b1 = false, b2 = false;
	return perform_find_ancestor(tree, n1, n2, b1, b2);
}

static const int N = 16;
static node *nodes[N] = { 0 };

void create_nodes() {
	for(int i = 0; i < N; i ++ ) nodes[i] = new node('a' + char(i));
}

void release_nodes() {
	for(int i = 0; i < N; i ++ ) delete nodes[i];
}

node *n(char idx) {
	return nodes[idx - 'a'];
}

int main(void) {
	create_nodes();

	n('a')->set_children(n('b'), n('c'));
	n('b')->set_children(n('d'), n('e'));
	n('c')->set_children(n('f'), n('g'));
	n('d')->set_children(n('h'), n('i'));
	n('e')->set_children(n('j'), n('k'));
	n('h')->set_children(n('l'), n('m'));
	n('i')->set_children(n('n'), NULL);

	///////////////////////////////////////////////////
	//
	//                     a
	//            b                 c
	//      d         e         f      g
	//   h     i    j   k
	//  l m   n
	//
	///////////////////////////////////////////////////

	node *tree = n('a');
	bool ok = true;

	node *anc = find_ancestor(tree, n('b'), n('c'));
	ok = anc == n('a');

	anc = find_ancestor(tree, n('n'), n('k'));
	ok = anc == n('b');

	anc = find_ancestor(tree, n('l'), n('m'));
	ok = anc == n('h');

	anc = find_ancestor(tree, n('b'), n('a'));
	ok = anc == NULL;

	anc = find_ancestor(tree, n('l'), n('g'));
	ok = anc == n('a');

	anc = find_ancestor(tree, n('m'), n('n'));
	ok = anc == n('d');

	anc = find_ancestor(tree, n('f'), n('g'));
	ok = anc == n('c');

	anc = find_ancestor(tree, n('h'), n('d'));
	ok = anc == n('b');

	anc = find_ancestor(tree, n('j'), n('j'));
	ok = anc == n('e');

	if(!ok) cout << "PROBLEM!" << endl;

	release_nodes();
	return 0;
}
