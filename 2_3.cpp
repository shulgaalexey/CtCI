/*
// 2.3 Implement an algorithm to delete a node in the middle of a singly linked list, given only access to that node.
// EXAMPLE
// Input: the node c from the linked list a->b->c->d->e
// Result: nothing is returned, but the new linked list lools like a->b->d->e

#include <iostream>

using namespace std;

class node {
public:
	char value;
	node *next;
	node(char v) : value(v), next(NULL) {}
};

void remove_from_middle(node *n) {
	if(!n || !n->next) return;
	node *tmp = n->next;
	n->value = n->next->value;
	n->next = n->next->next;
	delete tmp;
}

void trace(node *n) {
	while(n) {
		cout << n->value << " ";
		n = n->next;
	}
	cout << endl;
}

void release(node *l) {
	while(l) {
		node *n = l;
		l = l->next;
		delete n;
	}
}

int main() {
	node *a = new node('a');
	node *b = new node('b');
	node *c = new node('c');
	node *d = new node('d');
	node *e = new node('e');
	a->next = b;
	b->next = c;
	c->next = d;
	d->next = e;
	trace(a);
	remove_from_middle(c);
	trace(a);
	release(a);
	return 0;
}	
*/
