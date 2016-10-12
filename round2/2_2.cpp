#include <iostream>
using namespace std;

struct list {
	char data;
	list *next;
};

char find_kth_to_last(list *l, const int k) {
	list *p = l;
	for(int i = 0; i < k; i ++) {
		p = p->next;
		if(!p)
			return 'E';
	}

	list *p2 = l;
	while(p && p->next) {
		p = p->next;
		p2 = p2->next;
	}

	return p2->data;
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

	cout << find_kth_to_last(a, 0) << endl;
	cout << find_kth_to_last(a, 1) << endl;
	cout << find_kth_to_last(a, 2) << endl;
	cout << find_kth_to_last(a, 3) << endl;
	cout << find_kth_to_last(a, 4) << endl;

	return 0;
}
