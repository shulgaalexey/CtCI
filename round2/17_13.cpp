#include <iostream>
using namespace std;

struct binode {
	binode *n1;
	binode *n2;
	int data;
	binode(int d) : n1(NULL), n2(NULL), data(d) {}
};

struct list {
	binode *head;
	binode *tail;
	list() : head(NULL), tail(NULL) {}
};

list conv(binode *t) {
	if(!t)
		return list();

	list ret;

	if(t->n1) {
		list l = conv(t->n1);
		t->n1 = l.tail;
		t->n1->n2 = t;
		ret.head = l.head;
	} else {
		ret.head = t;
		ret.tail = t;
		t->n1 = NULL;
	}

	if(t->n2) {
		list l = conv(t->n2);
		t->n2 = l.head;
		t->n2->n1 = t;
		ret.tail = l.tail;
	} else {
		ret.head = t;
		ret.tail = t;
		t->n2 = NULL;
	}

	return ret;
}

int main(void) {
	binode *pool[7] = {0};
	for(int i = 0; i < 7; i ++)
		pool[i] = new binode(i);
	pool[3]->n1 = pool[1];
	pool[3]->n2 = pool[5];
	pool[1]->n1 = pool[0];
	pool[1]->n2 = pool[2];
	pool[5]->n1 = pool[4];
	pool[5]->n2 = pool[6];

	list l = conv(pool[3]);

	binode *h = l.head;
	while(h) {
		cout << h->data << " ";
		h = h->n2;
	}
	cout << endl;

	binode *t = l.tail;
	while(t) {
		cout << t->data << " ";
		t = t->n1;
	}
	cout << endl;

	return 0;
}

