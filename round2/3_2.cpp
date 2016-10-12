#include <iostream>
using namespace std;

class stack {
	int *buf;
	int *buf2; // maintaining current minimum of the stack
	int size;
	mutable int ptr;
	public:
	stack(const int n) : size(n), ptr(-1) {
		buf = new int[size];
		buf2 = new int[size];
	}
	~stack() {
		delete [] buf;
		delete [] buf2;
	}
	void push(int v) {
		buf[ptr + 1] = v;
		int cur_min = v;
		if((ptr >= 0) && (buf2[ptr] < v))
			cur_min = buf2[ptr];
		buf2[ptr + 1] = cur_min;
		ptr ++;
	}
	int pop() const {
		return buf[ptr --];
	}
	int min() const {
		return buf2[ptr];
	}
};

int main(void) {
	stack s(6);

	// Populate
	s.push(4);
	if(s.min() != 4) cout << "Err1" << endl;

	s.push(3);
	if(s.min() != 3) cout << "Err2" << endl;

	s.push(2);
	if(s.min() != 2) cout << "Err3" << endl;

	s.push(5);
	if(s.min() != 2) cout << "Err4" << endl;

	s.push(7);
	if(s.min() != 2) cout << "Err5" << endl;

	s.push(6);
	if(s.min() != 2) cout << "Err6" << endl;

	// Empty
	int v = s.pop();
	if((v != 6) && s.min() != 2) cout << "Err11" << endl;

	v = s.pop();
	if((v != 7) && s.min() != 2) cout << "Err12" << endl;

	v = s.pop();
	if((v != 5) && s.min() != 2) cout << "Err13" << endl;

	v = s.pop();
	if((v != 2) && s.min() != 3) cout << "Err14" << endl;

	v = s.pop();
	if((v != 3) && s.min() != 4) cout << "Err15" << endl;

	v = s.pop();
	if((v != 4)) cout << "Err16" << endl;

	cout << "OK" << endl;

	return 0;
}

