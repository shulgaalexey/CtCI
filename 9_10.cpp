// 9.10 You have a stack of n boxes, with width wi, height hi, and depth di.
// The boxes cannot be rotated and can only be stacked on top of one another if
// each box in the stack is strictly larger than the box above it in width,
// height, and depth.
// Implement a method to build the tallest stack possible, where the height of a
// stack is the sum of the hights of each box.

#include <iostream>
#include <vector>
#include <climits>
#include <map>
#include <stdlib.h>	// For rand
#include <time.h>	// For rand
using namespace std;

class box {
	public:
		int w;
		int h;
		int d;
		bool is_visited;
		unsigned int __id;
		static unsigned int __base_id;
	public:
		box() : w(INT_MAX), h(INT_MAX), d(INT_MAX), is_visited(false) {
			__id = __base_id ++;
		}
		box( int W, int H, int D) : w(W), h(H), d(D), is_visited(false) {
			__id = __base_id ++;
		}
	public:
		void visit() { is_visited = true; }
		void reset() { is_visited = false; }
		bool visited() const { return is_visited; }
};

unsigned int box::__base_id = 1;

class cache_item {
	public:
		vector<box> stack;
		int height;
	public:
		cache_item() : height(0) {}
		cache_item(const vector<box> st, int h) : height(h) {
			stack = st;
		}
		cache_item(const cache_item &src) {
			*this = src;
		}
		cache_item &operator = (const cache_item &src) {
			if(this != &src) {
				height = src.height;
				stack = src.stack;
			}
			return *this;
		}
};

map<unsigned int, cache_item> _m;

void print_source(const vector<box> &v) {
	cout << "Source: " << endl;
	for(size_t i = 0; i < v.size(); i ++)
		cout << v[i].w << "\t" << v[i].h << "\t" << v[i].d << endl;
}

void print_stack(const vector<box> &st) {
	cout << "Stack: " << endl;
	for(int i = int(st.size() - 1); i >= 0; i --)
		cout << st[i].w << "\t" << st[i].h << "\t" << st[i].d << endl;
}

int add_next_box_to_stack(vector<box> &st, vector<box> &v, int const cur_height, const box &top) {
	if(_m.count(top.__id) > 0) {	/* DP */
		cache_item ci = _m[top.__id];
		st = ci.stack;
		return ci.height;
	}

	int max_height = cur_height;
	vector<box> max_stack;
	for(size_t i = 0; i < v.size(); i ++) {
		if(v[i].visited())
			continue;
		if((v[i].w >= top.w) || (v[i].h >= top.h) || (v[i].d >= top.d))
			continue;
		v[i].visit();
		vector<box> cur_stack;
		cur_stack.push_back(v[i]);
		int height = add_next_box_to_stack(cur_stack, v, cur_height + v[i].h, v[i]);
		if(height > max_height) {
			max_height = height;
			max_stack = cur_stack;
		}
		v[i].reset();
	}
	for(size_t i = 0; i < max_stack.size(); i ++)
		st.push_back(max_stack[i]);

	_m[top.__id] = cache_item(st, max_height);	/* DP */
	return max_height;
}

void find_highest_box_stack(vector<box> &v) {
	//print_source(v);
	vector<box> max_stack;
	const int max_height = add_next_box_to_stack(max_stack, v, 0, box());
	cout << "Height: " << max_height << endl;
	print_stack(max_stack);
}

int main(void) {
	{ // Default test case
		cout << "Default test case 1" << endl;
		vector<box> v;
		v.push_back(box(15, 1, 16));
		v.push_back(box(17, 8, 8));
		v.push_back(box(7, 16, 13));
		v.push_back(box(4, 15, 4));
		v.push_back(box(4, 3, 4));
		find_highest_box_stack(v);
		cout << "---------------" << endl;
	}

	{ // Default test case
		cout << "Default test case 2" << endl;
		vector<box> v;
		v.push_back(box(15, 14, 13));
		v.push_back(box(16, 12, 18));
		v.push_back(box(9, 7, 6));
		v.push_back(box(10, 7, 6));
		v.push_back(box(5, 4, 3));
		find_highest_box_stack(v);
		cout << "---------------" << endl;
	}

	// Serial test
	srand(time(NULL));
	for(int test = 0; test < 5; test ++) {
		cout << "Test case #" << test << endl;
		vector<box> v;
		for(int i = 0; i < 5; i ++)
			v.push_back(box(rand() % 20, rand() % 20, rand() % 20));
		find_highest_box_stack(v);
		cout << "---------------" << endl;
	}

	{ // Complex case
		cout << "Complex Test case" << endl;
		vector<box> v;
		for(int i = 0; i < 1000; i ++)
			v.push_back(box(rand() % 50, rand() % 50, rand() % 50));
		find_highest_box_stack(v);
		cout << "---------------" << endl;
	}

	return 0;
}
