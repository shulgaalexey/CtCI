#include <iostream>
using namespace std;

struct list {
	char data;
	list *next;
};

//--------------------------------------------------------
list *l1 = NULL;
bool is_palindrome_recursive(list *l2) {
	if(l2 == NULL)
		return true; // reached the end of the list

	bool ret = is_palindrome_recursive(l2->next);

	ret &= l1->data == l2->data;
	l1 = l1->next;

	return ret;
}
//--------------------------------------------------------
list *reverse(list *l) {
	list *r = NULL;
	while(l) {
		list *tmp = r;
		r = new list;
		r->data = l->data;
		r->next = tmp;
		l = l->next;
	}
	return r;
}

bool is_palindrome(list *l) {
	list *r = reverse(l);
	while(r) {
		if(r->data != l->data)
			return false; // don't forget to release r
		r = r->next;
		l = l->next;
	}
	// Release r
	return true;
}
//--------------------------------------------------------

void trace(list *l) {
	while(l) {
		cout << l->data << " ";
		l = l->next;
	}
	cout << endl;
}

int main(void) {
	list *a1 = new list;
	a1->data = 'a';
	a1->next = NULL;

	list *b1 = new list;
	b1->data = 'b';
	b1->next = a1;

	list *c = new list;
	c->data = 'c';
	c->next = b1;

	list *b2 = new list;
	b2->data = 'b';
	b2->next = c;

	list *a2 = new list;
	a2->data = 'a';
	a2->next = b2;

	trace(a2);

	l1 = a2;
	if(!is_palindrome_recursive(l1))
		cout << "ERROR" << endl;
	else
		cout << "OK" << endl;

	if(!is_palindrome(l1))
		cout << "ERROR" << endl;
	else
		cout << "OK" << endl;
	return 0;
}
