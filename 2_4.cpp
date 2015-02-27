// 2.4 Write a code to partition a linked list around a value x, such that all nodes less than x,
// come before all nodes grater than or equal to x.

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

class node {
public:
	int value;
	node *next;
	node(int v) : value(v), next(NULL) {
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

node *append(node *l, int v) {
	if(!l) return new node(v);

	node *head = l;
	while(head->next) head = head->next;
	head->next = new node(v);
	return l;
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
	if(!greater) return less;
	greater->next = NULL; // Finalize the list
	// Concatenate: less->greater
	if (!less)
		return greater;
	less->next = greater_head;
	return less_head;
}

node *partition_book(node *l, const int x) {
	if(!l) return NULL;
	node *ptr = l;
	node *head = l;
	while(head->next) head = head->next;
	node *tail = head;
	const node *tail_ptr = tail;
	head = l;
	node *prev_ptr = l;
	while(ptr) {
		if(ptr == tail_ptr) break; // Finish: all nodes are processed
		if(ptr->value < x) {
			// Insert before head
				if(ptr!=head) {
					prev_ptr->next = ptr->next;
					ptr->next = head;
					head = ptr;
					ptr = prev_ptr->next;
				} else {
					prev_ptr = ptr;
					ptr = ptr->next;
				}
			//trace(head);
		} else {
			// Append after tail
			if(ptr!=tail) {
				if(ptr == prev_ptr) {
					head = head->next;
				    prev_ptr = head;
					ptr->next = NULL;
					tail->next = ptr;
					tail = tail->next;
					ptr = prev_ptr;
				} else {
					prev_ptr->next = ptr->next;
					ptr->next = NULL;
					tail->next = ptr;
					tail = tail->next;
					ptr = prev_ptr->next;
				}
			}
			//trace(head);
		   }
	}
	return head;
}

bool test(node *l, const int x) {
	bool b = false;
	while(l) {
		if(l->value >= x) b = true;
		if(b && (l->value < x)) return false;
		l = l->next;
	}
	return true;
}

node *gen_random_list(const int length) {
	node *l = NULL;
	for(int i = 0; i < length; i ++ )
		l = append(l, rand() % length);
	return l;
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
		node *l3 = copy(l);

		node *r = partition_inplace(l, pivot);
		node *r1 = partition_stupid(l1, pivot);
		node *r2 = partition_smart(l2, pivot);
		node *r3 = partition_book(l3, pivot);

		trace(r);
		trace(r1);
		trace(r2);
		trace(r3);

		if (!equal(r, r1))
			cout << "PROBLEM1" << endl;
		if (!equal(r, r2))
			cout << "PROBLEM2" << endl;
		if (!equal(r1, r2))
			cout << "PROBLEM3" << endl;
		if(!test(r3, pivot))
			cout << "PROBLEM!" << endl;

		release(l);
		release(l1);
		release(l2);
		release(l3);
	}

	{ // Main test #0
		int a[] = {1, 2, 2};
		node *l = NULL;
		for(size_t i = 0; i < (sizeof(a)/sizeof(a[0])); i ++ ) l = append(l, a[i]);
		//trace(l);
		l = partition_book(l, 1);
		//trace(l);
		if(!test(l,1)) cout << "PROBLEM!" << endl;
		release(l);
	}

	{ // Main test #1
		int a[] = {7, 8, 3, 5, 1, 10};
		node *l = NULL;
		for(size_t i = 0; i < (sizeof(a)/sizeof(a[0])); i ++ ) l = append(l, a[i]);
		//trace(l);
		l = partition_book(l, 5);
		//trace(l);
		if(!test(l,5)) cout << "PROBLEM!" << endl;
		release(l);
	}

	{ // Massive tests with random values
		srand(time(NULL));
		for(int length = 2; length < 100; length ++) {
			cout << "length: " << length << endl;
			for(int testno = 0; testno < (length * 3); testno ++) {

				node *l = gen_random_list(length);

				node *l1 = copy(l);
				node *l2 = copy(l);
				node *l3 = copy(l);
				node *l4 = copy(l);

				const int pivot = rand() % length;
				//cout << "Test: " << testno << ", x:" << pivot << ", list:" << endl;
				//trace(l);

				node *r1 = partition_inplace(l1, pivot);
				node *r2 = partition_stupid(l2, pivot);
				node *r3 = partition_smart(l2, pivot);
				node *r4 = partition_book(l4, pivot);

				bool b1 = test(r1, pivot);
				bool b2 = test(r2, pivot);
				bool b3 = test(r3, pivot);
				bool b4 = test(r4, pivot);

				if(!b1 || !b2 || !b3 || !b4) {
					cout << "PROBLEM in" << endl;
					if(!b1) cout << "\tinplace" << endl;
					if(!b2) cout << "\tstupid" << endl;
					if(!b3) cout << "\tsmart" << endl;
					if(!b4) cout << "\tbook" << endl;

					cout << "Test: " << testno << ", x:" << pivot << ", list:" << endl;
					trace(l);
				}

				release(l);
				release(l1);
				release(l2);
				release(l3);
				release(l4);
			}
		}
	}

	return 0;
}
