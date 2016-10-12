#include <iostream>
using namespace std;

struct list {
	char data;
	list *next;
};

char find_loop(list *l) {
	list *sr = l;
	list *fr = l;

	// Collide fast runner and slow runner
	do {
		sr = sr->next;
		fr = fr->next->next;
	} while(sr != fr);

	// Go back to the head and collide them again, but on the single speed
	sr = l;
	while(sr != fr) {
		sr = sr->next;
		fr = fr->next;
	}

	return sr->data;
}

int main(void) {
	list *a = new list;
	a->data = 'a';

	list *b = new list;
	b->data = 'b';

	list *c = new list;
	c->data = 'c';

	list *d = new list;
	d->data = 'd';

	list *e = new list;
	e->data = 'e';

	a->next = b;
	b->next = c;
	c->next = d;
	d->next = e;
	e->next = c; // This is a loop link

	cout << find_loop(a) << endl;

	return 0;
}
