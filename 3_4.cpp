// 3.4 In the classic problem of the Towers of Hanoi, you have 3 towers and N discs
// of different sizes which can slide onto any tower. The puzzle starts with discs sorted
// in ascending order of size from top to bottom (i.e., each disc sits on top of an even
// larger one). You have the following constraints:
// (1) Only one disc can be moved at a time.
// (2) A disc is slid off the top of one tower onto the next tower.
// (3) A disc can only be placed on top of a larger disc.
// Write a program to mave the discs from first tower to the last using stacks.
#include <iostream>
#include <stack>
using namespace std;

void trace(stack<char> s, const string &tag) {
	cout << "stack " << tag << ": ";
	if(s.empty()) {
		cout << "empty" << endl;
		return;
	}
	while(!s.empty()) {
		cout << s.top() << " ";
		s.pop();
	}
	cout << endl;
}

void trace_all(stack<char> A, stack<char> B, stack<char> C, int N) {
	cout << endl << "N = " << N << endl;
	trace(A, "A");
	trace(B, "B");
	trace(C, "C");
	cout << endl;
}

void move_top(stack<char> *s1, stack<char> *s2) {
	if(!s2->empty() && (s1->top() > s2->top())) { // It should never happen
		cout << "PROBLEM!" << endl;
		return;
	}
	s2->push(s1->top());
	s1->pop();
}

void rebase(stack<char> *A, stack<char> *B, stack<char> *C, const int N) {
	//trace_all(*A, *B, *C, N);
	if(N == 1) {
		move_top(A, B);
	} else if(N == 2) {
		move_top(A, C);
		move_top(A, B);
		move_top(C, B);
	} else {
		rebase(A, C, B, N-1);
		rebase(A, B, C, 1);
		rebase(C, B, A, N-1);
	}
}

int main(void)  {
	stack<char> A;
	for(char c = 'P'; c >= 'A'; c --) A.push(c);
	stack<char> B;
	stack<char> C;
	trace_all(A, B,  C, A.size());
	rebase(&A, &B, &C, A.size());
	trace_all(A, B,  C, A.size());

	return 0;
}
