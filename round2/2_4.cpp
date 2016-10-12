#include <iostream>
using namespace std;

struct list {
	int data;
	list *next;
};

list *partition(list *l, const int pivot) {
	list *gr = NULL;
	list *ls = NULL;

	list *h = l;
	while(h) {
		list *next = h->next;
		if(h->data >= pivot) {
			list *tmp = gr;
			gr = h;
			gr->next = tmp;
		} else {
			list *tmp = ls;
			ls = h;
			ls->next = tmp;
		}
		h = next;
	}

	l = ls;
	h = ls;
	while(h && h->next)
		h = h->next;
	h->next = gr;

	return l;
}

void trace(list *l) {
	while(l) {
		cout << l->data << " ";
		l = l->next;
	}
	cout << endl;
}

int main(void) {
	list *l1 = new list;
	l1->data = 9;
	l1->next = NULL;

	list *l2 = new list;
	l2->data = 7;
	l2->next = l1;

	list *l3 = new list;
	l3->data = 2;
	l3->next = l2;

	list *l4 = new list;
	l4->data = 5;
	l4->next = l3;

	list *l5 = new list;
	l5->data = 3;
	l5->next = l4;

	trace(l5);
	list *l = partition(l5, 4);
	trace(l);

	return 0;
}
