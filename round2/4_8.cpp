#include <iostream>
using namespace std;

struct tree {
	char data;
	tree *left;
	tree *right;
	tree(char c) : data(c), left(NULL), right(NULL) {};
};

bool __subtree = false;

bool match_tree(tree *T1, tree *T2) {
	if(!T1 && !T2)
		return true;
	if((T1 && !T2) || (!T1 && T2))
		return false;

	if(T1->data != T2->data)
		return false;
	return match_tree(T1->left, T2->left)
		&& match_tree(T1->right, T2->right);
}

void is_subtree(tree *T1, tree *T2) {
	if(__subtree)
		return;

	if(!T1 && !T2)
		return;

	if((T1 && !T2) || (!T1 && T2))
		return;

	if(T1->data == T2->data)
		__subtree = match_tree(T1, T2);

	if(__subtree)
		return;

	is_subtree(T1->left, T2);
	is_subtree(T1->right, T2);
}

int main(void) {

	tree *a = new tree('a');
	tree *b = new tree('b');
	tree *c = new tree('c');
	tree *d = new tree('d');
	tree *e = new tree('e');
	tree *f = new tree('f');
	tree *g = new tree('g');
	tree *h = new tree('h');
	tree *i = new tree('i');
	tree *j = new tree('j');
	tree *k = new tree('k');
	tree *l = new tree('l');
	tree *m = new tree('m');
	tree *n = new tree('n');
	tree *o = new tree('o');

	a->left = b;
	a->right = c;
	b->left = d;
	b->right = e;
	d->left = h;
	d->right = i;
	e->left = j;
	e->right = k;
	c->left = f;
	c->right = g;
	f->left = l;
	f->right = m;
	g->left = n;
	g->right = o;

	is_subtree(a, b);
	if(!__subtree)
		cout << "ERROR" << endl;
	else
		cout << "OK" << endl;

	return 0;
}
