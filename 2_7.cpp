// 2.7 Implement a function to check if a linked list a palindrome.

#include <iostream>
#include <string>
#include <stack>
using namespace std;

class  node {
	public:
		char value;
		node *next;
		node(char v) : value(v), next(NULL) {}
};

void trace(node *l) {
	while(l) {
		cout << l->value << " ";
		l = l->next;
	}
	cout << endl;
}

void release(node *l) {
	while(l) {
		node *n = l;
		l = l->next;
		delete n;
	}
}

node *add(node *l, char c) {
	node *n = new node(c);
	if(!l) return n;
	node *head = l;
	while(head->next) head = head->next;
	head->next = n;
	return l;
}

bool equal(node *a, node *b) {
	if(!a || !b) return true;
	while(a || b) {
		if(!a || !b) return false;
		if(a->value != b->value) return false;
		a = a->next;
		b = b->next;
	}
	return true;
}

class test_list {
	public:
		node *l;
	public:
		test_list(const string &s) : l(NULL) {
			for(size_t i = 0; i < s.length(); i ++) l = add(l, s[i]);
		}
		~test_list() { release(l); }
		operator node *() { return l; }
};

// Simple approach with a reverted list -------------------
//  1. Make a copy of the original list, but in reverse order
//  2. Compare original and reverted list
node *revert(node *l) {
	node *rev = NULL;
	while(l) {
		node *n = new node(l->value);
		if(!rev) {
			rev = n;
		} else {
			n->next = rev;
			rev = n;
		}
		l = l->next;
	}
	return rev;
}

bool is_palindrome_simple(node *l) {
	node *reverted_l = revert(l);
	const bool e = equal(l, reverted_l);
	release(reverted_l);
	return e;
}

// Recursive approach -------------------------------------
//  1. Move to the end of the list
//  2. Check if palindrom while backtracking
//    2.a Compare current head and current tail
//    2.b Go to next head and previous tail
class context {
	public:
		node *head_cmp;	// Moving head ptr for comparison
		bool finished;
		bool equal;
	public:
		context(node *l)
			: head_cmp(l)
			  , finished(false)
			  , equal(false) {}
};

void is_palindrome_rec(node *head, node *tail, context &ctx) {
	// 1. Going to the end of the list
	if(!tail) return; // Reached the end of the list
	is_palindrome_rec(head, tail->next, ctx);

	// 2. Checking if palindrome while backtracking
	if(ctx.finished) return; // Already know that finished (not equal)
	if(ctx.head_cmp->value == tail->value) {
		ctx.equal = true;
		if(ctx.head_cmp == tail)
			ctx.finished = true; // Middle node
		else
			ctx.head_cmp = ctx.head_cmp->next; // Move to next node
	} else  {
		ctx.equal = false;
		ctx.finished = true;
	}
}

bool is_palindrome(node *l) {
	if(!l) return true;
	context ctx(l);
	is_palindrome_rec(l, l, ctx);
	return ctx.equal;
}

// Linear (non-recursive) approach
//  1. Find a center of the list
//  2. Revert inplace second half of the list
//  3. Compare first and second parts of the list
bool is_palindrome_linear(node *l) {
	if(!l) return true;
	trace(l);

	// 1. Find a center of the list
	node *p = l;
	node *p2 = l; // fast runner ptr
	node *center = NULL;
	while(p2) {
		p = p->next;
		center = p;
		p2 = p2->next;
		if(!p2) break;
		p2 = p2->next;
	}
	trace(center);
	trace(l);

	// 2. Revert inplace second half of the list
	node *rev = NULL;
	while(center) {
		node *next = center->next;
		if(!rev) {
			rev = center;
			rev->next = NULL;
		} else {
			node *tmp = rev;
			rev = center;
			rev->next = tmp;
		}
		center = next;
	}
	center = rev;
	trace(center);
	trace(l);

	// 3. Compare first and second parts of the list
	while(center) {
		if(l->value != center->value) return false;
		l = l->next;
		center = center->next;
	}
	// parts of the inverted half of the list must be released in a more smart way
	return true;
}

// Using stack (as in the book) ---------------------------
// 1. Puth the first part of the list in the stack
// 2. Compare second part of the list with values from the stack
bool is_palindrome_stack(node *l) {
	if(!l) return true;

	// 1. Put the first part of the list in stack
	node *sp = l; // Slow runner
	node *fp = l; // Fast runner
	stack<char> s;
	node *center = NULL;
	while(fp) {
		center = sp;
		s.push(sp->value);
		sp = sp->next;
		fp = fp->next;
		if(!fp) break;
		fp = fp->next;
		if(!fp) center = center->next;
	}

	// 2. Compare second part of the list with values in stack
	while(center) {
		const char c = s.top();
		s.pop();
		if(c != center->value) return false;
		center = center->next;
	}
	return true;
}

// Tests --------------------------------------------------
int main(void) {

	{ // test1: OK
		test_list l1("ABCBA");
		const bool b1 = is_palindrome_simple(l1);

		test_list l2("ABCBA");
		const bool b2 = is_palindrome(l2);

		test_list l3("ABCBA");
		const bool b3 = is_palindrome_linear(l3);

		test_list l4("ABCBA");
		const bool b4 = is_palindrome_stack(l4);

		if(!b1 || !b2 || !b3 || !b4) cout << "PROBLEM!" << endl;
	}

	{ // test1: OK
		test_list l1("ABBA");
		const bool b1 = is_palindrome_simple(l1);

		test_list l2("ABBA");
		const bool b2 = is_palindrome(l2);

		test_list l3("ABBA");
		const bool b3 = is_palindrome_linear(l3);

		test_list l4("ABBA");
		const bool b4 = is_palindrome_stack(l4);

		if(!b1 || !b2 || !b3 ||!b4) cout << "PROBLEM!" << endl;
	}

	{ // test1: FAIL
		test_list l1("ABCA");
		const bool b1 = is_palindrome_simple(l1);

		test_list l2("ABCA");
		const bool b2 = is_palindrome(l2);

		test_list l3("ABCA");
		const bool b3 = is_palindrome_linear(l3);

		test_list l4("ABCA");
		const bool b4 = is_palindrome_stack(l4);

		if(b1 || b2 || b3 ||b4) cout << "PROBLEM!" << endl;
	}

	return 0;
}
