#include <iostream>
using namespace std;

struct list {
	char data;
	list *next;
};

void remove_duplicates(list *p) {
	while(p) {
		list *r = p;
		while(r) {
			if(r->next && (r->next->data == p->data)) {
				list *tmp = r->next;
				r->next = r->next->next;
				delete tmp;
			} else
				r = r->next;
		}
		p = p->next;
	}
}

void trace(list *l) {
	while(l) {
		cout << l->data << " ";
		l = l->next;
	}
	cout << endl;
}

int main(void) {
	list *c = new list;
	c->data = 'c';
	c->next = NULL;

	list *a1 = new list;
	a1->data = 'a';
	a1->next = c;

	list *b = new list;
	b->data = 'b';
	b->next = a1;

	list *a2 = new list;
	a2->data = 'a';
	a2->next = b;

	list *d = new list;
	d->data = 'd';
	d->next = a2;

	list *a3 = new list;
	a3->data = 'a';
	a3->next = d;

	list *l = a3;

	trace(l);
	remove_duplicates(l);
	trace(l);

	return 0;
}
