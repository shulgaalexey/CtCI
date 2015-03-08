// Stack and queue demo implementation
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

// Queue --------------------------------------------------
template <class T>
class queue {
	public:
		node<T> *head;
		node<T> *tail;
	public:
		queue() : head(NULL), tail(NULL) {}
		~queue();
	public:
		void enqueue(const T &v);
		T dequeue();
		bool empty() const;
};

template <class T>
queue<T>::~queue() {
	while(head) {
		node<T> *n = head;
		head = head->next;
		delete n;
	}
}

template <class T>
void queue<T>::enqueue(const T &v) {
	node<T> *n = new node<T>(v);
	if(!head) {
		head = n;
		tail = n;
	} else {
		tail->next = n;
		tail = tail->next;
	}
}

template <class T>
T queue<T>::dequeue() {
	if(!head) throw out_of_range("queue<>::dequeue empty queue");

	node<T> *n = head;
	T value = n->value;
	head = head->next;
	if(!head) tail = NULL;
	return value;
}

template <class T>
bool queue<T>::empty() const {
	return !head;
}

// Tests --------------------------------------------------
void test_stack(void) {
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
}

void test_queue(void) {
	{ // enqueue, dequeue
		queue<int> q;

		q.enqueue(1);
		q.enqueue(2);
		q.enqueue(3);

		if(q.dequeue() != 1) cout << "PROBLEM!" << endl;
		if(q.dequeue() != 2) cout << "PROBLEM!" << endl;
		if(q.dequeue() != 3) cout << "PROBLEM!" << endl;
	}

	/*try {
		queue<int> q;
		q.dequeue();
	} catch (exception const &ex) {
		const string str = ex.what();
		if(str != "queue<>::dequeue empty queue") cerr << "PROBLEM!" << endl;

	}*/

	{ // empty, enqueue
		queue<int> q;

		if(!q.empty()) cout << "PROBLEM!" << endl;

		q.enqueue(1);
		if(q.empty()) cout << "PROBLEM!" << endl;
	}
}

int main(void) {

	test_stack();

	test_queue();

	return 0;
}
