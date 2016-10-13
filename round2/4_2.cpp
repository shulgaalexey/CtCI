#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct node {
	char data;
	bool visited;
	vector<node *> adjucent;
	node(char c) : data(c), visited(false) {}
};

bool is_path_exists(const vector<node *> &G, node *A, node *B) {
	queue<node *> q;

	q.push(A);
	A->visited = true;

	while(!q.empty()) {
		node *n = q.front();
		q.pop();
		for(size_t i = 0; i < n->adjucent.size(); i ++) {
			node *adj = n->adjucent[i];
			if(adj == B)
				return true;
			if(adj->visited)
				continue;
			adj->visited = true;
			q.push(adj);
		}
	}
	return false;
}

int main(void) {
	node *a = new node('a');
	node *b = new node('b');
	node *c = new node('c');
	node *d = new node('d');
	node *e = new node('e');
	node *f = new node('f');

	vector<node *> G;
	G.push_back(a);
	G.push_back(b);
	G.push_back(c);
	G.push_back(d);
	G.push_back(e);
	G.push_back(f);

	a->adjucent.push_back(b);
	a->adjucent.push_back(f);

	c->adjucent.push_back(b);
	c->adjucent.push_back(d);

	e->adjucent.push_back(a);

	f->adjucent.push_back(c);

	if(!is_path_exists(G, a, d))
		cout << "Error1" << endl;
	if(is_path_exists(G, a, e))
		cout << "Error2" << endl;
	return 0;
}
