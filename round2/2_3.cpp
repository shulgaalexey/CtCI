#include <iostream>
using namespace std;

struct list {
	char data;
	list *next;
};

void delete_node(list *node) {
	if(!node || !node->next) {
		cout << "Exception: "
			"node must be in the middle of the list" << endl;
		return;
	}

	list *tmp = node->next;
	node->data = node->next->data;
	node->next = node->next->next;
	delete tmp;
}

void trace(list *l) {
	while(l) {
		cout << l->data << " ";
		l = l->next;
	}
	cout << endl;
}

int main(void) {

	list *d = new list;
	d->next = NULL;
	d->data = 'd';

	list *c = new list;
	c->next = d;
	c->data = 'c';

	list *b = new list;
	b->next = c;
	b->data = 'b';

	list *a = new list;
	a->next = b;
	a->data = 'a';

	trace(a);
	delete_node(c);
	trace(a);

	return 0;
}
