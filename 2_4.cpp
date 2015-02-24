
// 2.4 Write a code to partition a linked list around a value x, such that all nodes less than x,
// come before all nodes grater than or equal to x.

#include <iostream>
using namespace std;

class node {
public:
	int value;
	node *next;
	node(int v) :
			value(v), next(NULL) {
	}
};

void trace(node *l) {
	int cnt = 100;
	while (l && cnt) {
		cout << l->value << " ";
		l = l->next;
		cnt--;
	}
	cout << endl;
}

node *copy(node *l) {
	if (!l)
		return NULL;
	node *c = NULL, *c_head = NULL;
	while (l) {
		if (!c) {
			c = new node(l->value);
			c_head = c;
		} else {
			c->next = new node(l->value);
			c = c->next;
		}
		l = l->next;
	}
	return c_head;
}

bool equal(node *l1, node *l2) {
	if (!l1 && !l2)
		return true;
	while (l1 || l2) {
		if (!(l1 && l2))
			return false;
		if (l1->value != l2->value)
			return false;
		l1 = l1->next;
		l2 = l2->next;
	}
	return true;
}

void release(node *l) {
	while (l) {
		node *n = l;
		l = l->next;
		delete n;
	}
}

// in: a->p, b
// out: a->b->p
// return: b
node *insert_before(node *a, node *p, node *b) {
	if (!b)
		return (a) ? a : p;

	if (!a) {
		b->next = p;
	} else {
		a->next = b;
		b->next = p;
	}
	return b;
}

node *partition_inplace(node *list, int pivot) {
	// Using a sequence:
	//
	if (!list)
		return NULL;
	node *head = list;
	node *a = NULL;
	while (head) { // Shift to the first item to replace (greater than pivot)
		if (head->value >= pivot)
			break;
		a = head;
		head = head->next;
	}
	if (!head)
		return list; // Already arranged as required

	// Arranging the list
	node *ret = list;
	node *p = head;
	node *b = p->next;
	node *prev = p;
	while (b) {
		if (b->value < pivot) {
			node *tmp1 = b->next;
			a = insert_before(a, p, b);
			prev->next = tmp1;
			b = tmp1;
		} else {
			b = b->next;
			prev = prev->next;
		}
	}
	return ret;
}

node *partition_stupid(node *list, int pivot) {
	node *less = NULL, *less_head = NULL;// Collecting all "smaller" items in this list
	node *greater = NULL, *greater_head = NULL;	// Collecting all "bigger" items in this list
	node *head = list;
	while (head) {
		node *cur = new node(head->value);
		if (cur->value < pivot) {	// Add item to the "smaller" list
			if (!less) {
				less = cur;
				less_head = less;
			} else {
				less->next = cur;
				less = less->next;
			}
		} else {			// Add item to the "bigger" list
			if (!greater) {
				greater = cur;
				greater_head = greater;
			} else {
				greater->next = cur;
				greater = greater->next;

			}
		}
		head = head->next;
	}

	// Reconstructing resulting list:
	head = list;

	// 1. Adding "smaller" items
	less = less_head;
	while (less) {
		head->value = less->value;
		head = head->next;
		less = less->next;
	}

	// 2. Adding "bigger" items
	greater = greater_head;
	while (greater) {
		head->value = greater->value;
		head = head->next;
		greater = greater->next;
	}

	// 3. Releasing temporary lists
	while (less_head) {
		node *tmp = less_head;
		less_head = less_head->next;
		delete tmp;
	}
	while (greater_head) {
		node *tmp = greater_head;
		greater_head = greater_head->next;
		delete tmp;
	}

	return list;
}

node *partition_smart(node *list, int pivot) {
	node *less = NULL, *less_head = NULL;// Collectin small items in this list
	node *greater = NULL, *greater_head = NULL;	// Collecting big items in this list
	node *head = list;
	while (head) {
		if (head->value < pivot) {
			if (!less) {
				less = head;
				less_head = less;
			} else {
				less->next = head;
				less = less->next;
			}
		} else {
			if (!greater) {
				greater = head;
				greater_head = greater;
			} else {
				greater->next = head;
				greater = greater->next;
			}
		}
		head = head->next;
	}
	greater->next = NULL; // Finalize the list
	// Concatenate: less->greater
	if (!less)
		return greater;
	less->next = greater_head;
	return less_head;
}

int main() {
	{
		node *l = new node(1);
		l->next = new node(8);
		l->next->next = new node(9);
		l->next->next->next = new node(7);
		l->next->next->next->next = new node(6);
		l->next->next->next->next->next = new node(10);
		const int pivot = 8;

		trace(l);

		node *l1 = copy(l);
		node *l2 = copy(l);

		node *r = partition_inplace(l, pivot);
		node *r1 = partition_stupid(l1, pivot);
		node *r2 = partition_smart(l2, pivot);

		trace(r);
		trace(r1);
		trace(r2);

		if (!equal(r, r1))
			cout << "PROBLEM1" << endl;
		if (!equal(r, r2))
			cout << "PROBLEM2" << endl;
		if (!equal(r1, r2))
			cout << "PROBLEM3" << endl;

		release(l);
		release(l1);
		release(l2);
	}

	return 0;
}
