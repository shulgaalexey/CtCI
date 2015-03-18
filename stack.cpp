// Stack demo implementation
#include <iostream>
#include <stdexcept>
using namespace std;

// Node ---------------------------------------------------
template <class T>
class node {
	public:
		T value;
		node<T> *next;
	public:
		node(const T &v) : value(v), next(NULL) {}
};

// Stack --------------------------------------------------
template <class T>
class stack {
	public:
		node<T> *top;
	public:
		stack() : top(NULL) {}
		~stack();
	public:
		T pop();
		T peek() const;
		void push(const T &v);
		bool empty() const;
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
T stack<T>::pop() {
	if(!top) throw out_of_range("stack<>::pop empty stack");

	node<T> *n = top;
	T value = n->value;
	top = top->next;
	delete n;
	return value;
}

template <class T>
T stack<T>::peek() const {
	if(!top) throw out_of_range("stack<>::peek empty stack");
	return top->value;
}

template <class T>
void stack<T>::push(const T &v) {
	node<T> *n = new node<T>(v);
	n->next = top;
	top = n;
}

template <class T>
bool stack<T>::empty() const {
	return !top;
}


// Tests --------------------------------------------------
int main(void) {
	// pop, push
	{
		stack<int> s;
		s.push(1);
		s.push(2);
		s.push(3);

		if(s.pop() != 3) cout << "PROBLEM!" << endl;
		if(s.pop() != 2) cout << "PROBLEM!" << endl;
		if(s.pop() != 1) cout << "PROBLEM!" << endl;
	}
	/*try {
		stack<int> s;
		s.pop();
	} catch (exception const &ex) {
		const string str = ex.what();
		if(str != "stack<>::pop empty stack") cerr << "PROBLEM!" << endl;
	}*/

	// peek, push
	{
		stack<int> s;
		s.push(1);

		if(s.peek() != 1) cout << "PROBLEM!" << endl;
	}
	/*try {
		stack<int> s;
		s.pop();
	} catch (exception const &ex) {
		const string str = ex.what();
		//cerr << "Exception: " << str << endl;
		if(str != "stack<>::peek empty stack") cerr << "PROBLEM!" << endl;
	}*/

	{ // empty, push
		stack<int> s;

		if(!s.empty()) cout << "PROBLEM!" << endl;

		s.push(1);
		if(s.empty()) cout << "PROBLEM!" << endl;
	}
	return 0;
}
