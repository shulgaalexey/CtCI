#include <iostream>
using namespace std;

struct tree {
	int data;
	tree *parent;
	tree *left;
	tree *right;
	tree(int v) : data(v), parent(NULL), left(NULL), right(NULL) {}
};

tree *leftest(tree *n) {
	if(!n)
		return NULL;
	if(n->left)
		return leftest(n->left);
	else
		return n;
}

int find_next(tree *n) {
	if(n->right)
		return leftest(n->right)->data;

	while(n->parent && (n == n->parent->right))
		n = n->parent;
	if(!n->parent)
		return -1;
	return leftest(n->parent)->data;
}

int main(void) {
	tree *t = new tree(1); // TODO
	cout << find_next(t) << endl;
	return 0;
}
