#include <iostream>
using namespace std;

class stack {
	char *buf;
	const int size;
	mutable int pos;
	public:
	stack(const int n) : size(n), pos(-1) {
		buf = new char [size];
	}
	~stack() {
		delete [] buf;
	}
	void push(char c) {
		buf[++pos] = c;
	}
	char pop() const {
		return buf[pos--];
	}
	char pop_head() const {
		const char c = buf[0];
		for(int i = 1; i <= pos; i ++)
			buf[i - 1] = buf[i];
		pos --;
		return c;
	}
	bool empty() const {
		return (pos == (-1));
	}
	bool full() const {
		return (pos == (size - 1));
	}
};

struct list {
	stack data;
	list *prev;
	list *next;
	list(const int n) : data(n), prev(NULL), next(NULL) {}
};

class set_of_stacks {
	mutable list *set;
	const int stack_size;
	public:
	set_of_stacks(const int each) : set(NULL), stack_size(each) {}
	~set_of_stacks() {
		list *h = set;
		while(h) {
			list *next = h->next;
			delete h;
			h = next;
		}
		set = NULL;
	}
	void push(char c) {
		if(!set)
			set = new list(stack_size);

		list *tail = set;
		while(tail && tail->next)
			tail = tail->next;

		if(tail->data.full()) {
			tail->next = new list(stack_size);
			tail->next->prev = tail;
			tail = tail->next;
		}

		tail->data.push(c);
	}
	char pop() const {
		if(!set)
			return 'E'; // ERROR

		list *tail = set;
		while(tail && tail->next)
			tail = tail->next;

		const char c = tail->data.pop();

		if(tail->data.empty()) {
			if(tail == set) {
				delete tail;
				set = NULL;
			} else {
				tail->prev->next = NULL;
				delete tail;
			}
		}

		return c;
	}
	char pop_at(int index) {
		list *l = set;

		for(int i = 0; i < index; i ++) {
			if(!l)
				return 'E'; // ERROR
			l = l->next;
		}
		if(!l)
			return 'E'; // ERROR

		const char c = l->data.pop();

		if(l->data.empty()) {
			if(l == set) {
				delete l;
				set = NULL;
			} else {
				l->prev->next = NULL;
				delete l;
			}
		} else {
			while(l) {
				if(!l->next)
					break;
				l->data.push(l->next->data.pop_head());
				l = l->next;
			}
		}

		return c;
	}
};

int main(void) {
	set_of_stacks sos(5);

	for(int i = 0; i < 23; i ++) {
		sos.push('a' + i);
	}

	cout << sos.pop_at(2) << endl;

	for(int i = 0; i < 22; i ++)
		cout << sos.pop() << " ";
	cout << endl;

	return 0;
}
