// 4.2 Given a directed graph, design an algorithm to fid out
// whether there is a route between two nodes.
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class node_pool {
	private:
		vector<class node *> pool;
	public:
		~node_pool();
		void add(class node *n);
		void reset();
};

node_pool g_pool;

class node {
	public:
		char value;
		vector<node *> children;
		bool visited;
	public:
		node(char v);
		void connect(node *n);
};

node_pool::~node_pool() {
	for(size_t i = 0; i < pool.size(); i++)
		delete pool[i];
	pool.clear();
}

void node_pool::add(node *n) {
	pool.push_back(n);
}

void node_pool::reset() {
	for(size_t i = 0; i < pool.size(); i ++)
		pool[i]->visited = false;
}

node::node(char v) : value(v), visited(false) {
	g_pool.add(this);
}

void node::connect(node *n) {
	children.push_back(n);
}

// return BFS_connected(a,b) || BFS_connected(b,a)
bool is_connected(node *a, node *b, bool forward = true) {
	if(a == b) return true;
	if(!a && !b) return true;
	if(!a || !b) return false;

	queue<node *> q;
	q.push(a);
	while(!q.empty()) {
		node *n = q.front();
		q.pop();
		if(n==b) return true;
		n->visited = true;
		for(size_t i = 0; i < n->children.size(); i ++) {
			if(!n->children[i]->visited) {
				q.push(n->children[i]);
			}
		}
	}

	if(forward) {
		g_pool.reset();
		return is_connected(b, a, false);
	} else
		return false;
}

int main(void) {
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

	a->connect(b);
	a->connect(c);
	a->connect(d);

	c->connect(e);

	d->connect(c);
	d->connect(f);

	e->connect(g);

	h->connect(i);

	j->connect(g);

	bool ok = is_connected(a, g);
	g_pool.reset();

	ok &= is_connected(g, a);
	g_pool.reset();

	ok &= !is_connected(a, j);
	g_pool.reset();

	ok &= !is_connected(j, a);
	g_pool.reset();

	ok &= !is_connected(a, h);
	g_pool.reset();

	ok &= !is_connected(i, b);

	if(!ok) cout << "PROBLEM!" << endl;
	return 0;
}
