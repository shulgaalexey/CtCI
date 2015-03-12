// 3.3 imagine a (literal) stack of plates. if the stack gets too high, it might topple.
// Therefore, in real life, we would likely start a new stack when the previous stack
// exceeds some threshold. Implement a data structure SetOfStacks that mimics this.
// SetOfStacks should be composed of several stacks and should create a new stack
// once the previous exceeds capacity. SetOfStacks.push() and SetOfStacks.pop() should
// behave identically to a single stack (that is, pop() should return the same values
// as it would if there were just a single stack).
// FOLLOW UP
// Implement a function popAt(int index) which performs a pop operation on a
// specific sub-stack.

#include <iostream>
#include <stdexcept>
//#include <stdlib.h>
//#include <time.h>
#include <vector>
using namespace std;


//---------------------------------------------------------
template <class T>
class node {
	public:
		T value;
		node<T> *next;
	public:
		node(T v) : value(v), next(NULL) {}
};


//---------------------------------------------------------
template <class T>
class stack {
	public:
		node<T> *top;
		// It also seems good to remember the last item,
		// but for simplicity it is not done yet
		size_t capacity;
	public:
		stack() : top(NULL), capacity(0) {}

		~stack();
	public:
		bool empty() const { return !top; }
		T peek() const;
		T pop();
		void push(T v);
		size_t size() const { return capacity; }
		T extract_last();

	public:
		void trace();
};

template <class T>
stack<T>::~stack() {
	while(top) {
		node<T> *n = top;
		top = top->next;
		delete n;
	}
}

template <class T>
T stack<T>::peek() const {
	if(empty()) throw out_of_range("stack<>::peek empty stack");
	return top->value;
}

template <class T>
T stack<T>::pop() {
	if(empty()) throw out_of_range("stack<>::pop empty stack");
	T v = top->value;
	capacity --;
	node<T> *n = top;
	top = top->next;
	delete n;
	return v;
}

template <class T>
void stack<T>::push(T v) {
	node<T> *n = new node<T>(v);
	n->next = top;
	top = n;
	capacity ++;
}

template <class T>
T stack<T>::extract_last() {
	if(empty()) throw out_of_range("stack<>::extract_last empty stack");
	node<T> *n = top;
	if(!n->next)
		top = NULL;
	else {
		while(n->next->next) n = n->next;
		node<T> *tmp = n->next;
		n->next = NULL;
		n = tmp;
	}
	T v = n->value;
	delete n;
	capacity --;
	return v;
}

template <class T>
void stack<T>::trace() {
	node<T> *n = top;
	while(n) {
		cout << n->value << " ";
		n = n->next;
	}
	cout << endl;
}


//---------------------------------------------------------


template <class T>
class SetOfStacks {
	private:
		const size_t LIMIT;
	public:
		stack<stack<T> *> stacks;
	public:
		enum pop_at_type_e {RECURSIVE, LINEAR};
		pop_at_type_e pop_at_type;
	public:
		SetOfStacks(size_t limit, pop_at_type_e t = LINEAR) : LIMIT(limit), pop_at_type(t) {}
	public:
		bool empty() const { return stacks.empty(); }
		T peek() const { return stacks.peek()->peek(); }
		T pop();
		T popAt(int index);
		void push(T v);
	private:
		T popAt_recursive(int index, int cur, node<stack<T> *> *s);
		T popAt_linear(int  index);

	public:
		void trace();
};

template <class T>
T SetOfStacks<T>::pop() {
	T v = stacks.peek()->pop();
	if(stacks.peek()->empty())
		stacks.pop();
	return v;
}

template <class T>
void SetOfStacks<T>::push(T v) {
	if(empty() || (stacks.peek()->size() == LIMIT))
		stacks.push(new stack<T>());
	stacks.peek()->push(v);
}

template <class T>
T SetOfStacks<T>::popAt(int index) {
	switch(pop_at_type) {
		case RECURSIVE:	return popAt_recursive(index, 0, stacks.top);
		case LINEAR:	return popAt_linear(index);
		default:	throw out_of_range("SetOfStacks<> unknown popAt type");
	}
}

template <class T>
T SetOfStacks<T>::popAt_recursive(int index, int cur, node<stack<T>* > *n) {
	if(!n) throw out_of_range("SetOfStacks<>::popAt_recursive NULL node");
	if(index != cur) {
		T v = popAt_recursive(index, cur+1, n->next);
		T last = n->value->extract_last();
		n->next->value->push(last);
		if(n->value->empty()) stacks.pop(); // The top stack of stacks became empty
		return v;
	} else
		return n->value->pop();	// This is the desired item to pop
}

template <class T>
T SetOfStacks<T>::popAt_linear(int index) {
	if(empty()) throw out_of_range("SetOfStacks<>::popAt_linear empty stacks");
	stack<stack<T> *> bt; // backtracking
	node<stack<T> *> *n = stacks.top;
	for(int i = 0; i < index; i ++) {
		bt.push(n->value);
		n = n->next;
		if(!n) throw out_of_range("SetOfStacks<>::popAt_linear not enought depth");
	}

	T v = n->value->pop();
	stack<T> *prev = n->value;
	while(!bt.empty()) {
		stack<T> *s = bt.pop();
		T last = s->extract_last();
		prev->push(last);
		prev = s;
	}
	if(prev->empty()) stacks.pop();
	return v;
}

template <class T>
void SetOfStacks<T>::trace() {
	node<stack<T> *> *n = stacks.top;
	while(n) {
		n->value->trace();
		n = n->next;
	}
}

//---------------------------------------------------------
int main(void) {

	{ // Test of a stack
		stack<char> s;
		s.push('a');
		s.push('b');
		s.push('c');

		bool ok = true;
		char c = s.pop();
		ok &= c == 'c';
		c = s.pop();
		ok &= c == 'b';
		c = s.pop();
		ok &= c == 'a';

		if(!ok) cout << "PROBLEM!" << endl;
	}

	SetOfStacks<char> sos(3
			//, SetOfStacks::RECURSIVE
			);

	//srand(time(NULL));
	vector<char> v;
	//for(int i = 0; i < 10; i ++) v.push_back(0x41 + rand() % 26);
	for(int i = 0; i < 10; i ++) v.push_back(0x41 + i);

	for(size_t i = 0; i < v.size(); i ++) {
		char c = v[i];
		sos.push(c);
		//sos.trace();
	}


	for(int i = int(v.size() - 1); i >= 0; i --) {
		const char c = sos.pop();
		const char cur_v = v[i];
		//sos.trace();
		if(c != cur_v) {
			cout << "PROBLEM!" << endl;
			break;
		}
	}

	for(size_t i = 0; i < v.size(); i ++) {
		sos.push(v[i]);
		//sos.trace();
	}

	bool ok = true;
	char c = 0;

	c = sos.popAt(2);
	//sos.trace();
	ok &= c == 'F';

	c = sos.popAt(2);
	//sos.trace();
	ok &= c == 'C';

	c = sos.popAt(2);
	//sos.trace();
	ok &= c == 'D';

	c = sos.popAt(2);
	//sos.trace();
	ok &= c == 'E';

	c = sos.popAt(1);
	//sos.trace();
	ok &= c == 'G';

	if(!ok) cout << "PROBLEM!" << endl;

	return 0;
}
