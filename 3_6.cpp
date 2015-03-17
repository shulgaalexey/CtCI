// 3.6 Write a programm to sort a stack in ascending order (with biggest items on top).
// You may use at most one additional stack to hold items, but you may not copy the elements
// into any other data structure (such as an array).
// The stack supports the following operations: push, pop, peek, isEmpty

#include <iostream>
#include <stack>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

using namespace std;

// Variation of optimized bubble sort
template <class T>
bool separate(stack<T> &s1, stack<T> &s2, bool big) {
	bool changed = false;
	while(!s1.empty()) {
		const T v1 = s1.top();
		s1.pop();
		if(s1.empty()) {
			s2.push(v1);
			break;
		}
		// It may be implemented with a single temporary variable
		// but the method will be the same
		const T v2 = s1.top();
		s1.pop();
		if(big) { // separating bigger items
			if(v1 < v2) changed = true; // Order was changed
			s2.push(max(v1, v2));
			s1.push(min(v1, v2));
		} else { // separating smaller items
			if(v1 > v2) changed = true; // Order was changed
			s2.push(min(v1, v2));
			s1.push(max(v1, v2));
		}
	}
	return changed;
}

template <class T>
stack<T> *sort(stack<T> *s1, stack<T> *s2) {
	do {
		separate(*s1, *s2, true);
		if(!separate(*s2, *s1, false)) break;
	} while(true);

	return (s1->empty()) ? s2 : s1;
}

int main(void) {

	stack<int> s1; //unsorted
	stack<int> s2; // buffer

	s1.push(1);
	s1.push(5);
	s1.push(2);
	s1.push(8);
	s1.push(3);

	stack<int> *s = sort(&s1, &s2);

	while(!s->empty()) {
		cout << s->top() << " ";
		s->pop();
	}
	cout << endl;
	return 0;
}

