#include <iostream>
#include <stack>
using namespace std;

void sort(stack<char> *s1, stack<char> *s2) {

	bool l2r = true;
	while(true) {

		bool reordered = false;

		while(!s1->empty()) {
			if(s2->empty()) {
				s2->push(s1->top());
				s1->pop();
				continue;
			}

			bool cmp = (l2r)
				? (s1->top() < s2->top())
				: (s1->top() > s2->top());
			if(cmp) {
				s2->push(s1->top());
				s1->pop();
			} else {
				char tmp = s2->top();
				s2->pop();
				s2->push(s1->top());
				s1->pop();
				s2->push(tmp);

				reordered = true;
			}
		}

		if(!reordered)
			return;

		stack<char> *tmp = s1;
		s1 = s2;
		s2 = tmp;

		l2r = !l2r;
	}
}

int main(void) {

	stack<char> s1, s2;

	s1.push('d');
	s1.push('a');
	s1.push('c');
	s1.push('b');
	s1.push('e');

	sort(&s1, &s2);

	while(!s1.empty()) {
		cout << s1.top() << " ";
		s1.pop();
	}
	cout << endl;

	while(!s2.empty()) {
		cout << s2.top() << " ";
		s2.pop();
	}
	cout << endl;

	return 0;
}
