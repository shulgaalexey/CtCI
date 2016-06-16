// 18.9 Numbers are randomly generated and passed to a method. Write a program
// to find and maintain the median values as new values are generated.
#include <iostream>
#include <queue>
#include <stdlib.h>
#include <time.h>
using namespace std;

priority_queue<int> max_heap;
priority_queue<int> min_heap;

void add_number(int n) {
	if(max_heap.size() == min_heap.size()) {
		if(!min_heap.empty() && (n > min_heap.top())) {
			max_heap.push(min_heap.top());
			min_heap.pop();
			min_heap.push(n);
		} else
			max_heap.push(n);
	} else {
		if(n < max_heap.top()) {
			min_heap.push(max_heap.top());
			max_heap.pop();
			max_heap.push(n);
		} else
			min_heap.push(n);
	}
}

double get_median() {
	if(max_heap.empty())
		return .0;

	if(max_heap.size() == min_heap.size())
		return (double(min_heap.top()) + double(max_heap.top())) / 2;
	else
		return max_heap.top();
}

int main(void) {
	srand(time(NULL));

	vector<int> rnd_stream;
	for(int i = 0; i < 10; i ++) {
		const int n = rand() % 20;
		add_number(n);
		const double m = get_median();

		rnd_stream.push_back(n);
		for(size_t j = 0; j < rnd_stream.size(); j ++)
			cout << rnd_stream[j] << " ";
		cout << endl << m << endl << endl;
	}

	return 0;
}
