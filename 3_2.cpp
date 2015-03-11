// 3.2 How would you design a stack which,
// in addition to push and pop, also has a function min which returns the minimum element?
// Push, pop and min should all operate in O(1) time.
#include <iostream>
#include <stdexcept>
using namespace std;

//---------------------------------------------------------
class node {
	public:
		int value;
		int min;
		node *next;
	public:
		node(int v, int m) : value(v), min(m), next(NULL) {}
};

class stack {
	public:
		node *top;
	public:
		stack() : top(NULL) {}
		~stack();
	public:
		bool empty() const;
		int pop();
		void push(int v);
		int min() const;
};

stack::~stack() {
	while(top) {
		node *n = top;
		top = top->next;
		delete n;
	}
}

bool stack::empty() const {
	return !top;
}

int stack::pop() {
	if(empty()) throw out_of_range("stack::pop stack is empty");

	const int v = top->value;
	node *n = top;
	top = top->next;
	delete n;
	return v;
}

void stack::push(int v) {
	node *n = (empty()) ? (new node(v, v)) : (new node(v, std::min(min(), v)));
	n->next = top;
	top = n;
}

int stack::min() const {
	if(empty()) throw out_of_range("stack::min stack is empty");
	return top->min;
}

//---------------------------------------------------------
// Optimized stack of minimums (from the book)
class simple_node {
	public:
		int value;
		simple_node *next;
	public:
		simple_node(int v) : value(v), next(NULL) {}
};


class simple_stack {
	public:
		simple_node *top;
	public:
		simple_stack() : top(NULL) {}
		virtual ~simple_stack();
	public:
		bool empty() const;
		int peek() const;
	public:
		virtual int pop();
		virtual void push(int v);
};

simple_stack::~simple_stack() {
	while(top) {
		simple_node *n = top;
		top = top->next;
		delete n;
	}
}

bool simple_stack::empty() const {
	return !top;
}

int simple_stack::peek() const {
	if(empty()) throw out_of_range("simple_stack::peek stack is empty");
	return top->value;
}

int simple_stack::pop() {
	if(empty()) throw out_of_range("simple_stack::pop stack is empty");

	const int v = top->value;
	simple_node *n = top;
	top = top->next;
	delete n;
	return v;
}

void simple_stack::push(int v) {
	simple_node *n = new simple_node(v);
	n->next = top;
	top = n;
}


class stack2 : public simple_stack {
	simple_stack mins;
	public:
	stack2() {}
	virtual ~stack2() {}
	public:
	virtual int pop();
	virtual void push(int v);
	public:
	int min() const;
};

int stack2::pop() {
	int v = simple_stack::pop();
	if(v == mins.peek())
		mins.pop();
	return v;
}

void stack2::push(int v) {
	if(mins.empty())
		mins.push(v);
	else if(v <= mins.peek())
		mins.push(v);
	simple_stack::push(v);
}

int stack2::min() const {
	return mins.peek();
}

//---------------------------------------------------------
int main(void) {
	{
		stack s;
		bool ok = true;

		s.push(10);
		ok &= s.min() == 10;
		s.push(5);
		ok &= s.min() == 5;
		s.push(4);
		ok &= s.min() == 4;
		s.push(1);
		ok &= s.min() == 1;
		s.push(6);
		ok &= s.min() == 1;

		s.pop();
		ok &= s.min() == 1;
		s.pop();
		ok &= s.min() == 4;
		s.pop();
		ok &= s.min() == 5;
		s.pop();
		ok &= s.min() == 10;

		if(!ok) cout << "PROBLEM!" << endl;
	}

	{
		stack2 s;
		bool ok = true;

		s.push(10);
		ok &= s.min() == 10;
		s.push(5);
		ok &= s.min() == 5;
		s.push(4);
		ok &= s.min() == 4;
		s.push(1);
		ok &= s.min() == 1;
		s.push(6);
		ok &= s.min() == 1;

		s.pop();
		ok &= s.min() == 1;
		s.pop();
		ok &= s.min() == 4;
		s.pop();
		ok &= s.min() == 5;
		s.pop();
		ok &= s.min() == 10;

		if(!ok) cout << "PROBLEM!" << endl;
	}
	return 0;
}
