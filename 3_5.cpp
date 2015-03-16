// 3.5 Implement a MyQueue class which implements a queue using two stacks.
#include <iostream>
#include <stack>
#include <deque>
#include <stdlib.h>
#include <time.h>
#include <stdexcept>

using namespace std;

template <class T>
class MyQueue {
	private:
		mutable stack<T> head;
		mutable stack<T> tail;
		mutable enum {UNKNOWN, HEAD, TAIL} lastop;
	public:
		MyQueue() : lastop(UNKNOWN) {}
	public:
		bool empty() const;
		void enqueue(const T &v);
		T dequeue();
		T front() const;
		T back() const;
	private:
		void copy(stack<T> &src, stack<T> &dst) const;
};

template <class T>
bool MyQueue<T>::empty() const {
	if(lastop == UNKNOWN) return true;
	if(head.empty() && tail.empty()) return true;

	if(lastop == HEAD)
		copy(head, tail);
	else
		copy(tail, head);
	return (head.empty() && tail.empty());
}

template <class T>
void MyQueue<T>::enqueue(const T   &v) {
	if(lastop == TAIL) copy(tail, head);
	lastop = HEAD;
	head.push(v);
}

template <class T>
T MyQueue<T>::dequeue() {
	if(lastop == HEAD) copy(head, tail);
	lastop = TAIL;
	if(tail.empty()) throw out_of_range("MyQueue<>dequeue queue is empty");
	const T v = tail.top();
	tail.pop();
	return v;
}

template <class  T>
T MyQueue<T>::front() const {
	if(lastop == TAIL) copy(tail, head);
	lastop = HEAD;
	if(head.empty()) throw out_of_range("MyQueue<>front queue is empty");
	return head.top();
}

template <class T>
T MyQueue<T>::back() const {
	if(lastop == HEAD) copy(head, tail);
	lastop = TAIL;
	if(tail.empty()) throw out_of_range("MyQueue<>back queue is empty");
	return tail.top();
}

template <class T>
void MyQueue<T>::copy(stack<T> &src,  stack<T> &dst) const  {
	while(!dst.empty()) dst.pop();
	stack<T> tmp;
	while(!src.empty()) {
		dst.push(src.top());
		tmp.push(src.top());
		src.pop();
	}
	while(!tmp.empty()) {
		src.push(tmp.top());
		tmp.pop();
	}
}

typedef enum _QUEUE_OP_E {ENQUEUE, DEQUEUE, FRONT, BACK} QUEUE_OP_E;

int main(void) {
	MyQueue<char> mq;
	deque<char> q;
	bool ok = true;

	mq.enqueue('a');
	q.push_front('a');

	mq.enqueue('b');
	q.push_front('b');

	mq.enqueue('c');
	q.push_front('c');

	ok &= mq.front() == q.front();
	ok &= mq.back() == q.back();

	q.pop_back();
	mq.dequeue();
	ok &= mq.back() == q.back();

	srand(time(NULL));
	for(int testno = 0; testno < 10000; testno ++) {
		if((testno  % 1000) == 0) cout << "Test No: " << testno << endl;
		QUEUE_OP_E op = (QUEUE_OP_E)(rand() % 4);
		switch(op) {
			case ENQUEUE: {
							  const int n = rand()%10;
							  for(int i = 0; i < n; i ++) {
								  const char c = 'a' + (char)(rand()%26);
								  //cout << "Enqueue: " << c << endl;
								  mq.enqueue(c);
								  q.push_front(c);
							  }
							  break;
						  }
			case DEQUEUE: {
							  const int n = rand()%10;
							  for(int i = 0; i < n; i ++) {
								  if(mq.empty()) break;
								  const char c1 = mq.dequeue();
								  const char c2 = q.back();
								  q.pop_back();
								  ok &= c1 == c2;
								  //cout << "Dequeue " << c1 << endl;
							  }
							  break;
						  }
			case FRONT:
						  //cout << "Front" <<  endl;
						  if(mq.empty()) break;
						  ok &= mq.front() == q.front();
						  break;
			case BACK:
						  //cout << "Back" <<  endl;
						  if(mq.empty()) break;
						  ok &= mq.back() == q.back();
						  break;
			default:
						  cout << "UNKNOWN OPERATION!" << endl;
						  break;
		}
		if(!ok) {
			cout << "PROBLEM!" << endl;
			break;
		}
	}
	return 0;
}
