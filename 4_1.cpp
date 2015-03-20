// 4.1 Implement a function to check if a binary tree is balbnced. For the purpose of this
// question, a balanced tree is defined to be a tree such that the heights of the two
// subtrees of any node never differ by more than one.
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

// Node pull for garbage collection -----------------------
template <class T>
class node_pool {
	private:
		queue<T> pool;
	public:
		void add(T t);
		void free();
};

template <class T>
void node_pool<T>::add(T t) {
	pool.push(t);
}

template <class T>
void node_pool<T>::free() {
	while(!pool.empty()) {
		T t = pool.front();
		if(t) delete t;
		pool.pop();
	}
}

// Tree item ----------------------------------------------
class tree {
	public:
		char value;
		tree *left;
		tree *right;
		int depth; // For BFS-like approach
	public:
		tree(char v);
		bool has_children() const;
		void set_children(tree *l, tree *r);
};


static node_pool<tree *> g_pool;

tree::tree(char v) : value(v), left(NULL), right(NULL), depth(-1) {
	g_pool.add(this);
}

bool tree::has_children() const {
	return (left || right);
}

void tree::set_children(tree *l, tree *r) {
	left = l;
	right = r;
}


// Brute-force --------------------------------------------
int height(tree *t) {
	if(!t) return 0;
	return max(height(t->left), height(t->right)) + 1;
}

bool is_balanced_BF(tree *t) {
	if(!t) return true;
	if(!is_balanced_BF(t->left)) return false;
	if(!is_balanced_BF(t->right)) return false;
	//cout << "Node: " << t->value << "\tHL: " << height(t->left) << "\t HR: " << height(t->right) << endl;
	return (abs(height(t->left) - height(t->right)) <= 1);
}

// Better recursive approach ------------------------------
void perform_is_balanced_recursive(tree *t, int *h, bool *balanced) {
	if(!*balanced) return;
	if(!t) return;
	*h = *h + 1;
	if(!t->has_children()) return;

	if(!t->left && t->right && t->right->has_children()) {
		*balanced = false;
		return;
	}
	if(!t->right && t->left && t->left->has_children()) {
		*balanced = false;
		return;
	}

	int hl = 0;
	perform_is_balanced_recursive(t->left, &hl, balanced);
	if(!*balanced) return;

	int hr = 0;
	perform_is_balanced_recursive(t->right, &hr, balanced);
	if(!*balanced) return;

	*balanced = abs(hl - hr) <= 1;
	*h = max(hl, hr) + 1;
}

bool is_balanced_recursive(tree *t) {
	int h = 0;
	bool balanced = true;
	perform_is_balanced_recursive(t, &h, &balanced);
	return balanced;
}

// BFS-like approach --------------------------------------
void assign_depth(tree *t) {
	if(!t) return;
	if(!t->has_children()) {
		t->depth = 0;
		return;
	} else {
		if(t->depth < 0) {
			assign_depth(t->left);
			assign_depth(t->right);
			int dl = (t->left) ? t->left->depth : 0;
			int dr = (t->right) ? t->right->depth : 0;
			t->depth = max(dl, dr) + 1;
		}
		// else nothing to do: depth is calculated already
	}
}

bool is_balanced_BFS(tree *t) {
	if(!t) return true;
	assign_depth(t);
	queue<tree *> q;
	q.push(t);
	while(!q.empty()) {
		tree *cur = q.front();
		q.pop();
		if(cur->left) q.push(cur->left);
		if(cur->right) q.push(cur->right);
		int dl = (cur->left) ? cur->left->depth : 0;
		int dr = (cur->right) ? cur->right->depth : 0;
		if(abs(dl - dr) > 1) return false;
	}
	return true;
}

// Tests --------------------------------------------------
tree *gen_tree_1_p() {
	tree *a = new tree('a');
	tree *b = new tree('b');
	tree *c = new tree('c');
	tree *d = new tree('d');
	tree *e = new tree('e');
	tree *f = new tree('f');
	tree *g = new tree('g');
	tree *h = new tree('h');
	tree *i = new tree('i');

	d->set_children(b, c);
	e->set_children(a, d);
	i->set_children(e, h);
	h->set_children(f, g);

	return i;
}

tree *gen_tree_1_n() {
	tree *a = new tree('a');
	tree *b = new tree('b');
	tree *c = new tree('c');
	tree *d = new tree('d');
	tree *e = new tree('e');
	//tree *f = new tree('f');
	//tree *g = new tree('g');
	tree *h = new tree('h');
	tree *i = new tree('i');

	d->set_children(b, c);
	e->set_children(a, d);
	i->set_children(e, h);
	//h->set_children(f, g);

	return i;
}

tree *gen_tree_2_p() {
	tree *a = new tree('a');
	tree *b = new tree('b');
	tree *c = new tree('c');
	tree *d = new tree('d');
	tree *e = new tree('e');
	tree *f = new tree('f');
	tree *g = new tree('g');
	//tree *h = new tree('h');
	tree *i = new tree('i');
	tree *j = new tree('j');
	tree *k = new tree('k');
	tree *l = new tree('l');
	tree *m = new tree('m');
	tree *n = new tree('n');
	tree *o = new tree('o');
	tree *p = new tree('p');
	tree *q = new tree('q');

	a->set_children(b, k);
	b->set_children(c, d);
	c->set_children(e, f);
	f->set_children(g, NULL);//h);
	d->set_children(i, j);
	k->set_children(l, m);
	l->set_children(n, o);
	m->set_children(p, q);

	return a;
}

tree *gen_tree_2_n() {
	tree *a = new tree('a');
	tree *b = new tree('b');
	tree *c = new tree('c');
	tree *d = new tree('d');
	tree *e = new tree('e');
	tree *f = new tree('f');
	tree *g = new tree('g');
	//tree *h = new tree('h');
	tree *i = new tree('i');
	tree *j = new tree('j');
	tree *k = new tree('k');
	tree *l = new tree('l');
	tree *m = new tree('m');
	//tree *n = new tree('n');
	//tree *o = new tree('o');
	//tree *p = new tree('p');
	//tree *q = new tree('q');

	a->set_children(b, k);
	b->set_children(c, d);
	c->set_children(e, f);
	f->set_children(g, NULL);//h);
	d->set_children(i, j);
	k->set_children(l, m);
	//l->set_children(n, o);
	//m->set_children(p, q);

	return a;
}

tree *gen_tree_3_n() {
	tree *a = new tree('a');
	tree *b = new tree('b');
	tree *c = new tree('c');
	tree *d = new tree('d');
	tree *e = new tree('e');
	tree *f = new tree('f');
	tree *g = new tree('g');

	a->set_children(b, g);
	b->set_children(c, d);
	c->set_children(e, NULL);
	e->set_children(NULL, f);

	return a;
}

tree *gen_tree_4_n() {
	tree *a = new tree('a');
	tree *b = new tree('b');
	tree *c = new tree('c');
	tree *d = new tree('d');
	tree *e = new tree('e');
	tree *f = new tree('f');
	tree *g = new tree('g');

	a->set_children(b, g);
	b->set_children(c, d);
	c->set_children(e, NULL);
	e->set_children(f, NULL);

	return a;
}


class test_data {
	public:
		tree *t;
		bool b;
	public:
		test_data(tree *ptr, bool balanced) :t(ptr), b(balanced) {}
};

int main(void) {
	queue<test_data> test_queue; // Queue of trees to test

	// Simple positive test
	test_queue.push(test_data(gen_tree_1_p(), true));
	test_queue.push(test_data(gen_tree_1_n(), false));
	test_queue.push(test_data(gen_tree_2_p(), true));
	test_queue.push(test_data(gen_tree_2_n(), false));
	test_queue.push(test_data(gen_tree_3_n(), false));
	test_queue.push(test_data(gen_tree_4_n(), false));

	while(!test_queue.empty()) {
		test_data td = test_queue.front();
		test_queue.pop();
		if(is_balanced_BF(td.t) != td.b) cout << "PROBLEM: BF" << endl;
		if(is_balanced_recursive(td.t) != td.b) cout << "PROBLEM: Recursive" << endl;
		if(is_balanced_BFS(td.t) != td.b) cout << "PROBLEM: BFS" << endl;
	}

	g_pool.free();
	return 0;
}
