// 2.6 Giving a circular linked list, implement an algorithm which returns the node
// at the beginning of the loop.
// DEFINITION
// Circular linked list A (corrupted) is a linked list in which a node's next pointer points
// to an earlier node, so as to make a loop in the linked list.
// EXAMPLE
// Input: A->B->C->D->E->C [the same as C as earlier]
// Output: C

#include <iostream>
#include <map>
using namespace std;

class node {
	public:
		char value;
		int visit;
		node *next;
		node(char v) : value(v), visit(0), next(NULL) {}
};

node *detect_loop(node *l) {
	while(l) {
		if(++l->visit > 1) return l;
		l = l->next;
	}
	return NULL;
}

node *detect_map(node *l) {
	// not using "visit" field
	map<node*, bool> m;
	while(l) {
		if(m.count(l) > 0) return l;
		m[l] = true;
		l = l->next;
	}
	return NULL;
}

int main(void) {
	node *A = new node('A');
	node *B = new node('B');
	node *C = new node('C');
	node *D = new node('D');
	node *E = new node('E');

	{ // Normal test
		A->next = B;
		B->next = C;
		C->next = D;
		D->next = E;
		E->next = C;

		node *l = A;
		node *n1 = detect_loop(l);
		node *n2 = detect_map(l);

		if(n1 && (n1 == n2))
			cout << n1->value << endl;
		else
			cout << "PROBLEM! Dif algorithms!" << endl;
	}

	{ // Negative test
		E->next = NULL;	// un-loop
		node *l = A;
		while(l) {	// reset "visit" field
			l->visit = 0;
			l = l->next;
		}
		l = A;
		node *n1 = detect_loop(l);
		node *n2 = detect_map(l);
		if(n1 || n2)
			cout << "PROBLEM! Negative test failed!" << endl;
	}

	node *l = A;
	while(l) {
		node *n = l;
		l = l->next;
		delete n;
	}

	return 0;
}
