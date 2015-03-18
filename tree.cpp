// Demo implementation of a tree traversal methods
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

template <class T>
class node {
	public:
		T value;
		node<T> *left;
		node<T> *right;
	public:
		node(const T &v) : value(v), left(NULL), right(NULL) {}
};

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
		string get_string() const { return str; }
		void reset() { str.clear(); }
};

template <class T>
void str_visitor<T>::visit(node<T> *n) {
	if(!n) return;
	ostringstream oss;
	oss << n->value;
	str += oss.str();
}

template <class T>
class release_visitor : public visitor<T> {
	public:
		virtual ~release_visitor() {}
		virtual void visit(node<T> *n) { if(n) delete n; }
};

template <class T>
void preorder(node<T> *t, visitor<T> *v) {
	if(!t) return;
	preorder(t->left, v);
	if(v) v->visit(t);
	preorder(t->right, v);
}

template <class T>
void inorder(node<T> *t, visitor<T> *v) {
	if(!t) return;
	if(v) v->visit(t);
	inorder(t->left, v);
	inorder(t->right, v);
}

template <class T>
void postorder(node<T> *t, visitor<T> *v) {
	if(!t) return;
	postorder(t->left, v);
	postorder(t->right, v);
	if(v) v->visit(t);
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
	node<char> *j = new node<char>('j');
	node<char> *k = new node<char>('k');

	d->left = e;
	c->left = d;
	c->right = f;
	b->left = c;
	b->right = g;
	a->left = b;

	i->left = j;
	h->left = i;
	h->right = k;
	a->right = h;


	str_visitor<char> sv;

	preorder(a, &sv);
	//cout << sv.get_string() << endl << "edcfbgajihk" << endl;
	if(sv.get_string() != "edcfbgajihk") cout << "PROBLEM!" << endl;
	sv.reset();

	inorder(a, &sv);
	//cout << sv.get_string() << endl << "abcdefghijk" << endl;
	if(sv.get_string() != "abcdefghijk") cout << "PROBLEM!" << endl;
	sv.reset();

	postorder(a, &sv);
	//cout << sv.get_string() << endl << "edfcgbjikha" << endl;
	if(sv.get_string() != "edfcgbjikha") cout << "PROBLEM!" << endl;
	sv.reset();

	release_visitor<char> rv;
	postorder(a, &rv);

	return 0;
}
