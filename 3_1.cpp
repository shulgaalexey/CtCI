// 3.1 Describe how you could use a single array to implement three stacks
#include <iostream>
#include <stdexcept>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

#ifndef DEBUG
//#define DEBUG
#endif //DEBUG

typedef unsigned char uchar;

// First stack is started at 0 and goes to the right
// Second stack is started at (n-1) and goes to the left
// Third stack is started in the middle of empty space between first and second stacks and goes
//   to the left for each odd push
//   to the right for each even push
//
//   |S1->        <-S3>      <--S2|
// __________________________________________________________________
// Actually this approach uses four stacks while the middle two stacks
// are combined into single "mutant-stack"
class stack3 {
	public:
		uchar *buf;
		const int n;

		mutable int a;	// Steps from left
		mutable int b;	// Steps from right
		mutable int cl;	// Left border of third (middle) stack
		mutable int cr;	// Right border of third (middle) stack
		mutable int step;
	public:
		stack3(const int size);	// Total size of the buffer for all three stacks
		~stack3();
	public:
		void push1(const uchar v);
		void push2(const uchar v);
		void push3(const uchar v);

		uchar pop1() const;
		uchar pop2() const;
		uchar pop3() const;

		bool empty1() const;
		bool empty2() const;
		bool empty3() const;
	private:
		void repartition();
		void trace(const string &tag);
	private:
		void dbg_clear();
		friend bool simple_test();
		friend bool random_test(bool need_repartition);
		friend bool single_repartition_a_test();
		friend bool single_repartition_b_test();
};

	stack3::stack3(const int size)
	: n(size)
	, a(-1)
	, b(-1)
	, cl(-1)
	  , cr(-1)
	  , step(-1) {
		  buf = new uchar[n];
		  dbg_clear();
	  }

stack3::~stack3() {
	delete [] buf;
}

bool stack3::empty1() const {
	return (a < 0);
}

bool stack3::empty2() const {
	return (b < 0);
}

bool stack3::empty3() const {
	return (cl < 0);
}

void stack3::push1(const uchar v) {
	a ++;
	if((a+b+step+3) > n) {
		a --;
		throw out_of_range("stack3::push1");
	}
	if(!empty3() && (a >= cl))
		repartition();
	buf[a] = v;
}

void stack3::push2(const uchar v) {
	b ++;
	if((a+b+step+3) > n) {
		b --;
		throw out_of_range("stack3::push2");
	}
	if(!empty3() && ((n-1-b) <= cr))
		repartition();
	buf[n-1-b] = v;
}

void stack3::push3(const uchar v) {
	step ++;
	if((a+b+step+3) > n) {
		step --;
		throw out_of_range("stack3::push3");
	}
	if(empty3()) {
		int center = (n + std::max(0,int(a)) - std::max(0,int(b))) / 2;
		cl = center -1;
		cr = center;
	}
	if(step & 1) {
		if(step > 1) cl --;
		if(cl < 0) throw out_of_range("stack3::push3: not enough space");
		buf[cl] = v;
	} else {
		if(step > 1) cr ++;
		if(cr >= n) throw out_of_range("stack::push3: not enough space"); // This is meaningless
		buf[cr] = v;
	}
}

uchar stack3::pop1() const {
	if(empty1()) throw out_of_range("stack3::pop1");
#ifndef DEBUG
	return buf[a--];
#else
	const uchar v = buf[a];
	buf[a] = 42;
	a --;
	return v;

#endif //DEBUG
}

uchar stack3::pop2() const {
	if(empty2()) throw out_of_range("stack3:pop2");
#ifndef DEBUG
	return buf[n-1-b--];
#else
	const uchar v = buf[n-1-b];
	buf[n-1-b] = 42;
	b --;
	return v;
#endif //DEBUG
}

uchar stack3::pop3() const {
	if(empty3()) throw out_of_range("stack3:pop3");
#ifndef DEBUG
	const uchar v = (step-- & 1) ? buf[cl++] : buf[cr--];
#else
	uchar v = 0;
	if(step & 1) {
		v = buf[cl];
		buf[cl] = 42;
		cl ++;
	} else {
		v = buf[cr];
		buf[cr] = 42;
		cr --;
	}
	step --;
#endif //DEBUG
	if(step < 0) {
		cl = -1;
		cr = -1;
	}
	return v;
}

void stack3::repartition() {
#ifdef DEBUG
	trace("Before repartition");
#endif //DEBUG
	if((cl < 0) || (cr < 0)) cerr << "Attempting to repartition without middle stack!" << endl;
	const int center = (n + std::max(0,int(a)) - std::max(0,int(b))) / 2;
	const int old_center = cl + (cr - cl) / 2 + 1;
	const int d = center - old_center;
	if(d > 0) {
		for(int i = cr; i >= cl; i --) {
			buf[i+d] = buf[i];
#ifdef DEBUG
			buf[i] = 42;
#endif // DEBUG
		}
		cl += d;
		cr += d;
	} else {
		for(int i = cl; i <= cr; i ++) {
			buf[i+d] = buf[i];
#ifdef DEBUG
			buf[i] = 42;
#endif // DEBUG
		}
		cl += d;
		cr += d;
	}
#ifdef DEBUG
	trace("After repartition");
#endif //DEBUG
}

void stack3::dbg_clear()  {
	for(int i = 0; i < n; i ++) buf[i] = 42;
}

void stack3::trace(const string &tag ) {
	cout << tag << endl;
	for(int i = 0; i < n; i ++) {
		if(buf[i] == 42) cout << "__ ";
		else cout << setw(2) << int(buf[i]) << " ";
	}
	cout << endl;
}

// Tests --------------------------------------------------
bool simple_test() {
	cout << "Simple Test" << endl;
	stack3 s(3);

	bool ok = true;
	s.push1(10);
	s.push1(20);
	s.push1(30);
	ok &= s.pop1() == 30;
	ok &= s.pop1() == 20;
	ok &= s.pop1() == 10;
	if(!ok) {
		cout << "PROBLEM: push1&pop1" << endl;
		return false;
	}
	s.dbg_clear();

	ok = true;
	s.push2(40);
	s.push2(50);
	s.push2(60);
	ok &= s.pop2() == 60;
	ok &= s.pop2() == 50;
	ok &= s.pop2() == 40;
	if(!ok) {
		cout << "PROBLEM: push2&pop2" << endl;
		return false;
	}
	s.dbg_clear();

	ok = true;
	s.push3(70);
	s.push3(80);
	s.push3(90);
	ok &= s.pop3() == 90;
	ok &= s.pop3() == 80;
	ok &= s.pop3() == 70;
	if(!ok) {
		cout << "PROBLEM: push3&pop3" << endl;
		return false;
	}
	s.dbg_clear();

	ok = true;
	s.push1(100);
	s.push2(110);
	s.push3(120);
	ok &= s.pop1() == 100;
	ok &= s.pop2() == 110;
	ok &= s.pop3() == 120;
	if(!ok) {
		cout << "PROBLEM: push&pop 1,2,3" << endl;
		return false;
	}

	return true;
}

vector<uchar> gen_rand(const int M) {
	vector<uchar> v;
	int size = std::max(rand() % M, M / 4);
	for(int i = 0; i < size; i ++) {
		const uchar uc = rand() % 100;
		if(uc == 42) continue;
		v.push_back(uc);
	}
	return v;
}

uchar extract_first(vector<uchar> &v) {
	const uchar uc = v[0];
	v.erase(v.begin());
	return uc;
}

uchar extract_last(vector<uchar> &v) {
	const uchar uc = v[v.size() - 1];
	v.pop_back();
	return uc;
}

void trace(const string &tag, const vector<uchar> &v) {
	cout << tag << ", size: " << v.size() << endl;
	for(size_t i = 0; i <  v.size(); i ++) cout << setw(2) << int(v[i]) << " "; cout << endl;
}


bool random_test(bool need_repartition) {
	cout << "Random Test";
	if(need_repartition) cout << " with repartition";
	cout << endl;

	const int M = 10;
	vector<uchar> v1 = gen_rand(M);
	vector<uchar> v1_res = v1;
#ifdef DEBUG
	trace("v1", v1);
#endif // DEBUG

	vector<uchar> v2 = gen_rand(M);
	vector<uchar> v2_res = v2;
#ifdef DEBUG
	trace("v2", v2);
#endif // DEBUG

	vector<uchar> v3 = gen_rand(M);
	vector<uchar> v3_res = v3;
#ifdef DEBUG
	trace("v3", v3);
#endif //DEBUG

	const int stack_size = (need_repartition)
		? (v1.size() + v2.size() + v3.size())
		: (3 * M);
	stack3 s(stack_size);
	while(!v1.empty() || !v2.empty() || !v3.empty()) {
		const int v = 1 + rand() % 3;
		switch(v) {
			case 1:
				if(!v1.empty())
					s.push1(extract_first(v1));
				break;
			case 2:
				if(!v2.empty())
					s.push2(extract_first(v2));
				break;
			case 3:
				if(!v3.empty())
					s.push3(extract_first(v3));
				break;
			default:
				cout << "ERROR: Out of arrays" << endl;
				break;
		}
#ifdef DEBUG
		s.trace("s");
#endif//_DEBUG
	}
	//s.trace("s");

	bool ok = true;
	while(!s.empty1() || !s.empty2() || !s.empty3()) {
		const int v = 1 + rand() % 3;
		switch(v) {
			case 1: {
						if(s.empty1()) break;
						const uchar sval = s.pop1();
						const uchar vval = extract_last(v1_res);
						ok = sval == vval;
						//ok = s.pop1() == extract_last(v1_res);
						break;
					}
			case 2: {
						if(s.empty2()) break;
						const uchar sval = s.pop2();
						const uchar vval = extract_last(v2_res);
						ok = sval == vval;
						//ok = s.pop2() == extract_last(v2_res);
						break;
					}
			case 3: {
						if(s.empty3()) break;
						const uchar sval = s.pop3();
						const uchar vval = extract_last(v3_res);
						ok = sval == vval;
						//ok = s.pop3() == extract_last(v3_res);
						break;
					}
			default:
					cout << "ERROR: Out of arrays" << endl;
					break;
		}
#ifdef DEBUG
		s.trace("S");
#endif //DEBUG
	}

	ok &= v1_res.empty() && v2_res.empty() && v3_res.empty();
	if(!ok) cout << "PROBLEM" << endl;

	return ok;
}

bool single_repartition_a_test() {
	cout << "Test Repartition: moving to the right ->" << endl;
	stack3 s(10);

	s.push3(5);
	s.push3(4);

	s.push2(9);

	s.push1(10);
	s.push1(11);
	s.push1(12);

	s.push1(13);

	s.push1(14);
	s.push1(15);
	s.push1(16);

#ifdef DEBUG
	s.trace("s");
#endif //DEBUG

	return true;
}

bool single_repartition_b_test() {
	cout << "Test Repartition: moving to the left <---" << endl;
	stack3 s(10);

	s.push3(5);
	s.push3(4);

	s.push1(10);

	s.push2(9);
	s.push2(8);
	s.push2(7);

	s.push2(6);

	s.push2(51);
	s.push2(52);
	s.push2(53);

#ifdef DEBUG
	s.trace("s");
#endif //DEBUG

	return true;
}

int main(void) {

	srand(time(NULL));

	// Simple test: push and pop small amount of items into three stacks
	if(!simple_test()) return -1;

	// Testing re-partition of the middle stack
	// from the left to the right after left stack increased significantly
	if(!single_repartition_a_test()) return -1;

	// Testing re-partition of the middle stack
	// from the right to the left after right stack increased significantly
	if(!single_repartition_b_test()) return -1;

	// Testing random operations with stack3 (without re-partitioning)
	for(int test = 0; test < 1000; test ++)
		if(!random_test(false)) return -1;

	// Testing random operations with stack3 (with re-partitioning)
	for(int test = 0; test < 1000; test ++)
		if(!random_test(true)) return -1;

	cout << endl << "FINISHED SUCCESSFULY" << endl << endl;
	return 0;
}
