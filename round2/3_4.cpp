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
	void trace() const {
		if(pos < 0) {
			cout << "-----" << endl;
			return;
		}
		for(int i = 0; i <= pos; i ++)
			cout << buf[i] << " ";
		cout << endl;
	}

};

void move(stack *from, stack *to) {
	to->push(from->pop());
}

void rebase(stack *A, stack *B, stack *C, int N) {
	if(N == 0)
		return;
	else if(N == 1)
		move(A, B);
	else if(N == 2) {
		move(A, C);
		move(A, B);
		move(C, B);
	} else {
		rebase(A, C, B, N - 1);
		rebase(A, B, C, 1);
		rebase(C, B, A, N - 1);
	}
}

int main(void) {
	stack A(5);
	stack B(5);
	stack C(5);

	A.push('e');
	A.push('d');
	A.push('c');
	A.push('b');
	A.push('a');

	A.trace();
	B.trace();
	C.trace();
	cout << "calculating..." << endl;
	rebase(&A, &B, &C, 5);
	A.trace();
	B.trace();
	C.trace();

	return 0;
}
