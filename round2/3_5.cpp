#include <iostream>
#include <stack>
using namespace std;

class my_queue {
	stack<char> s1;
	stack<char> s2;
	public:
	void enque(char c) {
		s2.push(c);
	}
	char deque() {
		if(s1.empty()) {
			while(!s2.empty()) {
				s1.push(s2.top());
				s2.pop();
			}
		}

		const char c = s1.top();
		s1.pop();
		return c;
	}
};

int main(void) {

	my_queue q;

	q.enque('a');
	q.enque('b');
	q.enque('c');
	q.enque('d');

	cout << q.deque() << endl; // expected 'a'

	q.enque('e');

	cout << q.deque() << endl; // expected 'b'
	cout << q.deque() << endl; // expected 'c'
	cout << q.deque() << endl; // expected 'd'
	cout << q.deque() << endl; // expected 'e'

	return 0;
}
