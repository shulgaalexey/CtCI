// Demo of DFS and BFS
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

using namespace std;

template <class T>
class list {
	public:
		T value;
		list<T> *prev;
		list<T> *next;
	public:
		list(const T &v) : value(v), prev(NULL), next(NULL) {}
};

template <class T>
class queue {
	private:
		list<T> *head;
		list<T> *tail;
	public:
		queue() : head(NULL), tail(NULL) {}
	public:
		void enqueue(const T &v);
		T dequeue();
		bool empty() const;
};

template <class T>
bool queue<T>::empty() const {
	return (!head);
}

template <class T>
void queue<T>::enqueue(const T &v) {
	list<T> *l = new list<T>(v);
	if(head) {
		head->prev = l;
		l->next = head;
		head = l;
	} else {
		head = l;
		tail = l;
	}
}

template <class T>
T queue<T>::dequeue() {
	if(empty()) throw out_of_range("queue<>::dequeue empty queue");
	const T v = tail->value;
	if(tail->prev) {
		list<T> *tmp = tail->prev;
		delete tail;
		tail = tmp;
		tail->next = NULL;
	} else {
		head = NULL;
		delete tail;
		tail = NULL;
	}
	return v;
}

template <class T>
class node {
	public:
		T value;
		bool visited;
		list<node<T> *> *children;
	public:
		node(const T &v) : value(v), visited(false), children(NULL) {}
	public:
		void add_child(node<T> *n);
};

template <class T>
void node<T>::add_child(node<T> *n) {
	list<node<T> *> *child = new list<node<T> *>(n);
	if(!children)
		children = child;
	else {
		list<node<T> *> *head = children;
		while(head->next) head = head->next;
		head->next = child;
		child->prev = head;
	}
}

template <class T>
class visitor {
	public:
		visitor() {}
		virtual ~visitor() {}
		virtual void visit(node<T> *n) = 0;
};

template <class T>
class str_visitor : public visitor<T> {
	private:
		string str;
	public:
		virtual ~str_visitor() {}
		virtual void visit(node<T> *n);
	public:
		void reset() { str.clear(); }
		string get_string() const { return str; }
};

template <class T>
void str_visitor<T>::visit(node<T> *n) {
	if(!n) return;
	ostringstream oss;
	oss << n->value;
	str += oss.str();

	//cout << str << endl;
}

template <class T>
class release_visitor : public visitor<T> {
	public:
		virtual ~release_visitor() {}
		virtual void visit(node<T> *n) { if(n) delete n; }
};

template <class T>
class reset_visitor : public visitor<T> {
	public:
		virtual ~reset_visitor() {}
		virtual void visit(node<T> *n) { if(n) n->visited = false; }
};


template <class T>
void DFS(node<T> *n, visitor<T> *v) {
	if(!n) return;
	n->visited = true;
	if(v) v->visit(n);
	if(!n->children) return;
	list<node<T> *> *l = n->children;
	while(l) {
		if(!l->value->visited)
			DFS(l->value, v);
		l = l->next;
	}
}

template <class T>
void BFS(node<T> *n, visitor<T> *v) {
	if(!n) return;
	n->visited = true;
	if(v) v->visit(n);

	queue<node<T> *> q;
	q.enqueue(n);
	while(!q.empty()) {
		node<T> *cur = q.dequeue();
		list<node<T> *> *l = cur->children;
		while(l) {
			if(!l->value->visited) {
				l->value->visited = true;
				if(v) v->visit(l->value);
				q.enqueue(l->value);
			}
			l = l->next;
		}
	}
}

template <class T>
class node_pull {
	private:
		list<node<T> *> *pull;
	public:
		node_pull() : pull(NULL) {}
	public:
		void add(node<T> *n);
		void visit_all(visitor<T> *v);

};

template <class T>
void node_pull<T>::add(node<T> *n) {
	list<node<T> *> *item = new list<node<T> *>(n);
	if(pull) {
		item->next = pull;
		pull->prev = item;
	}
	pull = item;
}

template <class T>
void node_pull<T>::visit_all(visitor<T> *v) {
	if(!v) return;
	list<node<T> *> *l = pull;
	while(l) {
		v->visit(l->value);
		l = l->next;
	}
}


int main(void) {
	node<char> *a = new node<char>('a');
	node<char> *b = new node<char>('b');
	node<char> *c = new node<char>('c');
	node<char> *d = new node<char>('d');
	node<char> *e = new node<char>('e');
	node<char> *f = new node<char>('f');
	node<char> *g = new node<char>('g');
	node<char> *h = new node<char>('h');
	node<char> *i = new node<char>('i');

	node_pull<char> np;
	np.add(a);
	np.add(b);
	np.add(c);
	np.add(d);
	np.add(e);
	np.add(f);
	np.add(g);
	np.add(h);
	np.add(i);

	//////////////////
	//              //
	//        d     //
	//       / \    //
	//     /b---e   //
	//    / |\ /    //
	//   /  | f     //
	//  a   |       //
	//   \  | g     //
	//    \ |/ \    //
	//     \c---h   //
	//       \ /    //
	//        i     //
	//              //
	//////////////////

	e->add_child(d);
	e->add_child(b);
	e->add_child(f);

	h->add_child(g);
	h->add_child(c);
	h->add_child(i);

	b->add_child(c);
	b->add_child(d);
	b->add_child(e);
	b->add_child(f);

	c->add_child(b);
	c->add_child(g);
	c->add_child(h);
	c->add_child(i);

	a->add_child(b);
	a->add_child(c);

	str_visitor<char> sv;

	BFS(a, &sv);
	cout << sv.get_string() << endl << "abcdefghi" << endl;
	if(sv.get_string() != "abcdefghi") cout << "PROBLEM!" << endl;
	sv.reset();

	reset_visitor<char> resv;
	np.visit_all(&resv);

	DFS(a, &sv);
	cout << sv.get_string() << endl << "abcghidef" << endl;
	if(sv.get_string() != "abcghidef") cout << "PROBLEM!" << endl;

	release_visitor<char> relv;
	np.visit_all(&relv);

	return 0;
}
