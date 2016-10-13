#include<iostream>
using namespace std;

struct tree {
	char data;
	tree *left;
	tree *right;
	tree(char c) : data(c), left(NULL), right(NULL) {}
};

tree *ancestor = NULL;

void includes(tree *t, tree *A, tree *B, bool *a, bool *b) {
	if(!t)
		return;

	includes(t->left, A, B, a, b);
	if(*a && *b && !ancestor)
		ancestor = t;

	includes(t->right, A, B, a, b);
	if(*a && *b && !ancestor)
		ancestor = t;

	if(t == A)
		*a = true;
	if(t == B)
		*b = true;
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

	bool afound = false;
	bool bfound = false;
	includes(a, i, e, &afound, &bfound);

	cout << ancestor << endl;
	if(ancestor)
		cout << ancestor->data << endl; // expected b
	return 0;
}
