#include <iostream>
#include <vector>
using namespace std;

struct list {
	char data;
	list *next;
	list(char c) : data(c), next(NULL) {}
};

struct tree {
	char data;
	tree *left;
	tree *right;
	tree(char c) : data(c), left(NULL), right(NULL) {}
};

vector<list *> levels;

void create_list(tree *t, int depth) {
	if(!t)
		return;

	if(int(levels.size()) < (depth + 1))
		levels.push_back(new list(t->data));
	else {
		list *l = levels[depth];
		while(l && l->next)
			l = l->next;
		l->next = new list(t->data);
	}

	create_list(t->left, depth + 1);
	create_list(t->right, depth + 1);
}

void trace(list *l) {
	while(l) {
		cout << l->data << " ";
		l = l->next;
	}
	cout << endl;
}

int main(void) {
	tree *a = new tree('a');
	tree *b = new tree('b');
	tree *c = new tree('c');
	tree *d = new tree('d');
	tree *e = new tree('e');
	tree *f = new tree('f');
	tree *g = new tree('g');

	a->left = b;
	a->right = c;
	b->left = d;
	b->right = e;
	c->left = f;
	c->right = g;

	create_list(a, 0);

	for(size_t i = 0; i < levels.size(); i ++)
		trace(levels[i]);

	// Expected
	// a
	// b c
	// d e f g

	return 0;
}
