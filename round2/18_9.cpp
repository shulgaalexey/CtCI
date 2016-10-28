#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
using namespace std;

class heap {
	protected:
		vector<int> data;
		int size;
	public:
		heap() : size(0) {}
		void push(int d) {
			size ++;
			if(int(data.size()) < size)
				data.push_back(d);
			else
				data[size - 1] = d;
			swap(0, size - 1);
			heapify(0);
		}
		int top() const { return data[0]; }
		int get_size() const { return size; }
		void pop() {
			swap(0, size - 1);
			size --;
			heapify(0);
		}
		void swap(int i, int j) {
			int tmp = data[i];
			data[i] = data[j];
			data[j] = tmp;
		}
		void heapify(int i ) {
			int left = 2 * i + 1;
			if((left < size) && !condition(i, left)) {
				swap(i, left);
				heapify(left);
			}

			int right = 2 * i + 2;
			if((right < size) && !condition(i, right)) {
				swap(i, right);
				heapify(right);
			}
		}
		virtual bool condition(int i, int j) = 0;
};

class max_heap : public heap {
	public:
		virtual bool condition(int i, int j) {
			return data[i] >= data[j];
		}
};

class min_heap : public heap {
	public:
		virtual bool condition(int i, int j) {
			return data[i] <= data[j];
		}
};

max_heap mx;
min_heap mn;
int median = 0;

int on_stream(int d) {
	if(!median) {
		mx.push(d);
		median = d;
		return median;
	}

	if(d > median)
		mn.push(d);
	else
		mx.push(d);

	if((mx.get_size() - mn.get_size()) > 1) {
		do {
			mn.push(mx.top());
			mx.pop();
		} while(mn.get_size() < mx.get_size());
	}

	if((mn.get_size() - mx.get_size()) > 0) {
		do {
			mx.push(mn.top());
			mn.pop();
		} while(mx.get_size() <= mn.get_size());
	}

	if(mx.get_size() > mn.get_size())
		median = mx.top();
	else
		median = (mn.top() + mx.top()) / 2;
	return median;
}

int main(void) {
	srand(time(NULL));
	vector<int> input;
	for(int i = 0; i < 10; i ++) {
		const int d = rand() % 10;
		input.push_back(d);
		on_stream(d);
		cout << "in: " << d << endl;
		for(size_t j = 0; j < input.size(); j++)
			cout << input[j] << " ";
		cout << endl;
		cout << "median: " << median << endl << endl;
	}
	return 0;
}
