// 2.5 You have two numbers represented by a linked list, where each node contains a single digit.
// The digits are stored in reverse order, such that the 1's digit is at the head of the list.
// Write a function that adds the two numbers and returns the sum as  a linked list.
// EXAMPLE
// Input: (7->1->6) + (5->9->2). That is 617 + 295.
// Output: 2->1->9. that is 912.
// FOLLOW UP
// Suppose the digits are stored in forward order. Repeat the above problem.
// EXAMPLE
// Input: (6->1->7) + (2->9->5). that is 617 + 295.
// Output: 9->1->2. That is 912.

#include <iostream>
using namespace std;

class node {
	public:
		int value;
		node *next;
		node(int v) : value(v), next(NULL) {}
};

// Service functions --------------------------------------
bool equal(node *a, node *b) {
	if(!a && !b) return true;
	while(a || b) {
		if(!a || !b) return false;
		if(a->value != b->value) return false;
		a = a->next;
		b = b->next;
	}
	return true;
}

void release(node *l) {
	while(l) {
		node *n = l;
		l = l->next;
		delete n;
	}
}

void trace(node *l) {
	while(l) {
		cout << l->value << " ";
		l = l->next;
	}
	cout << endl;
}

// Backward task ------------------------------------------
node *sum_bw(node *a, node *b) {
	node *res = NULL;
	node *res_head = NULL;
	int buf = 0;
	while(a || b) {
		node *tmp = new node(buf);
		if(a) tmp->value += a->value;
		if(b) tmp->value += b->value;
		buf = tmp->value / 10;
		tmp->value %= 10;
		if(!res) {
			res = tmp;
			res_head = tmp;
		} else {
			res->next = tmp;
			res = res->next;
		}
		if(a) a = a->next;
		if(b) b = b->next;
	}
	if(buf) {	// final addition if needed (overflow)
		if(!res_head)
			res_head = new node(buf); // for zero case
		else
			res->next = new node(buf);
	}
	return res_head;
}

int list2int_bw(node *l) {
	int num = 0, radix = 1;
	while(l) {
		num += l->value * radix;
		radix *= 10;
		l = l->next;
	}
	return num;
}

node *int2list_bw(int n) {
	node *res = NULL;
	node *res_head = NULL;
	do {
		node *tmp = new node(n%10);
		n  /= 10;
		if(!res) {
			res = tmp;
			res_head = res;
		} else {
			res->next = tmp;
			res = res->next;
		}
	} while(n > 0);
	return res_head;
}

node *sum_bw_smallN(node *a, node *b) {
	return int2list_bw(list2int_bw(a) + list2int_bw(b));
}

// Forward task -------------------------------------------
node *stabilize_length(node *llong, node *lshort) {
	while(llong) {
		node *nil = new node(0);
		nil->next = lshort;
		lshort = nil;
		llong = llong->next;
	}
	return lshort;
}

node *sum_fw_rec(node *a, node *b, int *over) {
	if(!a || !b) {
		*over = 0;
		return NULL;
	}
	node *tail = sum_fw_rec(a->next,  b->next, over);
	node *res = new node(a->value + b->value + *over);
	*over = res->value / 10;
	res->value %= 10;
	res->next = tail;
	return res;
}

node *sum_fw(node *a, node *b) {
	node *a_tmp = a;
	node *b_tmp = b;
	while(a && b) {
		a = a->next;
		b = b->next;
	}
	if(a||b) {
		if(a) {
			b = stabilize_length(a, b_tmp);
			a = a_tmp;
		}
		else {
			a = stabilize_length(b, a_tmp);
			b = b_tmp;
		}
	} else {
		a = a_tmp;
		b = b_tmp;
	}
	int over = 0;
	node *res = sum_fw_rec(a, b, &over);
	if(over) {
		node *one = new node(1);
		one->next = res;
		res = one;
	}
	return res;
}

int list2int_fw(node *l, int *radix) {
	if(!l) {
		*radix = 1;
		return 0;
	}
	int tail = list2int_fw(l->next, radix);
	int res = l->value * *radix + tail;
	*radix *= 10;
	return res;
}

node *int2list_fw(int n) {
	node *res = NULL;
	do {
		node *tmp = new node(n % 10);
		n /= 10;
		if(!res) {
			res = tmp;
		} else {
			tmp->next = res;
			res = tmp;
		}
	} while(n > 0);
	return res;
}

node *sum_fw_smallN(node *a, node *b) {
	int radix_a = 0,  radix_b = 0;
	return int2list_fw(list2int_fw(a, &radix_a) + list2int_fw(b, &radix_b));
}


// Main tests----------------------------------------------
int main(void) {
	{ // Backward case, normal test
		node *a = new node(7);
		a->next = new node(1);
		a->next->next = new node(6);

		node *b = new node(5);
		b->next = new node(9);
		b->next->next = new node(2);

		node *s1 = sum_bw(a,  b);
		trace(s1);
		node *s2 = sum_bw_smallN(a, b);
		trace(s2);

		if(!equal(s1, s2)) cout << "PROBLEM!" << endl;

		release(s1);
		release(s2);
		release(a);
		release(b);
	}

	//if(0)
	{ // Backward case,  random tests
		const int MAX_VAL = 9999;
		for(int i = 0; i < MAX_VAL; i ++) {
			node *a = int2list_bw(i);
			cout << "Bacward: a=" << i << endl;
			for(int j = 0; j < MAX_VAL; j ++) {
				//cout << "Bacward: a=" << i << ", b=" << j << endl;
				node *b = int2list_bw(j);

				node *s1 = sum_bw(a,  b);
				node *s2 = sum_bw_smallN(a, b);

				if(!equal(s1, s2)) {
					cout << "PROBLEM!" << endl;
					trace(a);
					cout << "\t+" << endl;
					trace(b);
					trace(s1);
					trace(s2);
					cout << "---------------" << endl;
					return 1;
				}

				release(s1);
				release(s2);
				release(b);
			}
			release(a);
		}
	}

	{ // Forward case, normal test
		node *a = new node(6);
		a->next = new node(1);
		a->next->next = new node(7);

		node *b = new node(2);
		b->next = new node(9);
		b->next->next = new node(5);

		node *s1 = sum_fw(a, b);
		trace(s1);
		node *s2 = sum_fw_smallN(a, b);
		trace(s2);

		if(!equal(s1, s2)) cout << "PROBLEM!" << endl;

		release(s1);
		release(s2);
		release(a);
		release(b);
	}

	//if(0)
	{ // Forward case,  random tests
		const int MAX_VAL = 9999;
		for(int i = 0; i < MAX_VAL; i ++) {
			node *a = int2list_fw(i);
			cout << "Forward a=" << i << endl;
			for(int j = 0; j < MAX_VAL; j ++) {
				//cout << "Forward a=" << i << ", b=" << j << endl;
				node *b = int2list_fw(j);

				node *s1 = sum_fw(a,  b);
				node *s2 = sum_fw_smallN(a, b);

				if(!equal(s1, s2)) {
					cout << "PROBLEM!" << endl;
					trace(a);
					cout << "\t+" << endl;
					trace(b);
					trace(s1);
					trace(s2);
					cout << "---------------" << endl;
					return 1;
				}

				release(s1);
				release(s2);
				release(b);
			}
			release(a);
		}
	}


	return 0;
}
