// Queue demo implementation
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
int main(void) {
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

	return 0;
}
