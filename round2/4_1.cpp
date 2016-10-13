#include <iostream>
using namespace std;

struct node {
	char data;
	node *left;
	node *right;
	node(char c) : data(c), left(NULL), right(NULL) {}
};

int abs(int a) {
	return (a >= 0) ? a : ((-1) * a);
}

int get_height(node *t) {
	if(!t)
		return 0;
	return max(get_height(t->left), get_height(t->right)) + 1;
}

bool is_balanced(node *t) {
	return abs(get_height(t->left) - get_height(t->right)) <= 1;
}

int main(void) {
	node *a = new node('a');
	node *b = new node('b');
	node *c = new node('c');
	node *d = new node('d');
	node *e = new node('e');
	node *f = new node('f');
	node *g = new node('g');

	a->left = b;
	a->right = c;
	b->left = d;
	b->right = e;
	if(!is_balanced(a))
		cout << "ERROR1" << endl;

	e->left = f;
	if(is_balanced(a))
		cout << "ERROR2" << endl;

	c->right = g;
	if(!is_balanced(a))
		cout << "ERROR3" << endl;

	return 0;
}
