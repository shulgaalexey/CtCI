// 4.4 Give a binary tree, design an algorithm which creates a linked list of all
// the nodes at each depth (e.g./ if yu have a tree with depth D,  you'll have D linked lists).
#include <iostream>
#include <list>
#include <vector>
#include <queue>
using namespace std;

class node {
	public:
		char value;
		node *left;
		node *right;
	public:
		node(char v);
		void set_children(node *l = NULL, node *r = NULL) {
			left = l;
			right = r;
		}
		static void release_pool();
};

static vector<node *> pool;

node::node(char v) : value(v), left(NULL), right(NULL) {
	pool.push_back(this);
}

void node::release_pool() {
	for(size_t i = 0; i < pool.size(); i ++)
		delete pool[i];
	pool.clear();
}


// Using BFS ----------------------------------------------
vector<list<node *> > tree2list_bfs(node *tree) {
	vector<list<node *> > v;
	queue<node *> q;
	q.push(tree);
	q.push(NULL);
	list<node *> l;
	while(!q.empty()) {
		node *n = q.front();
		q.pop();
		if(n) {
			l.push_back(n);
			if(n->left) q.push(n->left);
			if(n->right) q.push(n->right);
		} else {
			v.push_back(l);
			if(q.empty() || !q.front()) break;
			l.clear();
			q.push(NULL);
		}
	}
	return v;
}

// Using DFS ----------------------------------------------
void perform_tree2list_dfs(node *tree, int level, vector<list<node *> > &v) {
	if(!tree) return;
	perform_tree2list_dfs(tree->left, level + 1, v);
	perform_tree2list_dfs(tree->right, level + 1, v);
	if(v.empty()) v.resize(level + 1);
	v[level].push_back(tree);
}

vector<list<node *> > tree2list_dfs(node *tree) {
	vector<list<node *> > v;
	perform_tree2list_dfs(tree, 0, v);
	return v;
}

// Testing ------------------------------------------------
void trace(const vector<list<node *> > &v) {
	for(vector<list<node *> >::const_iterator it = v.begin(); it != v.end(); ++it) {
		for(list<node *>::const_iterator lit = (*it).begin(); lit != (*it).end(); ++lit) {
			cout << (*lit)->value << " ";
		}
		cout << endl;
	}
	cout << endl;
}

class node_pool {
	public:
		~node_pool() {
			node::release_pool();
		}
};

int main(void) {
	node_pool np;

	///////////////////////////////////////////////////
	//                       a
	//             b--------------------c
	//       d----------e----------f----------g
	//    h-----i----j----------k-----l----m
	//  n--o
	///////////////////////////////////////////////////

	node *a = new node('a');
	node *b = new node('b');
	node *c = new node('c');
	node *d = new node('d');
	node *e = new node('e');
	node *f = new node('f');
	node *g = new node('g');
	node *h = new node('h');
	node *i = new node('i');
	node *j = new node('j');
	node *k = new node('k');
	node *l = new node('l');
	node *m = new node('m');
	node *n = new node('n');
	node *o = new node('o');

	a->set_children(b, c);
	b->set_children(d, e);
	c->set_children(f, g);
	d->set_children(h, i);
	e->set_children(j);
	f->set_children(k, l);
	g->set_children(m);
	h->set_children(n, o);

	vector<list<node *> > vbfs = tree2list_bfs(a);
	vector<list<node *> > vdfs = tree2list_dfs(a);

	trace(vbfs);
	trace(vdfs);

	return 0;
}
