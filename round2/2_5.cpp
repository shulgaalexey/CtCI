#include <iostream>
using namespace std;

struct list {
	int data;
	list *next;
};

list *sum(list *l1, list *l2) {
	int add = 0;
	list *result = NULL;
	list *result_tail = NULL;
	while(l1 && l2) {
		const int res = (l1->data + l2->data + add) % 10;
		add = (l1->data + l2->data + add) / 10;
		if(!result) {
			result = new list;
			result->data = res;
			result->next = NULL;
			result_tail = result;
		} else {
			result_tail->next = new list;
			result_tail = result_tail->next;
			result_tail->data = res;
			result_tail->next = NULL;
		}
		l1 = l1->next;
		l2 = l2->next;
	}

	while(l1) {
		if(!result) {
			result = new list;
			result->data = l1->data;
			result->next = NULL;
			result_tail = result;
		} else {
			result_tail->next = new list;
			result_tail = result_tail->next;
			result_tail->data = l1->data;
			result_tail->next = NULL;
		}
		l1 = l1->next;
	}

	while(l2) {
		if(!result) {
			result = new list;
			result->data = l2->data;
			result->next = NULL;
			result_tail = result;
		} else {
			result_tail->next = new list;
			result_tail = result_tail->next;
			result_tail->data = l2->data;
			result_tail->next = NULL;
		}
		l2 = l2->next;
	}

	return result;
}

void trace(list *l) {
	while(l) {
		cout << l->data << " ";
		l = l->next;
	}
	cout << endl;
}

int main(void) {

	list *l11 = new list;
	l11->data = 6;
	l11->next = NULL;

	list *l12 = new list;
	l12->data = 1;
	l12->next = l11;

	list *l13 = new list;
	l13->data = 7;
	l13->next = l12;

	list *l21 = new list;
	l21->data = 2;
	l21->next = NULL;

	list *l22 = new list;
	l22->data = 9;
	l22->next = l21;

	list *l23 = new list;
	l23->data = 5;
	l23->next = l22;

	trace(l13);
	trace(l23);
	list *l = sum(l13, l23);
	trace(l);

	return 0;
}
