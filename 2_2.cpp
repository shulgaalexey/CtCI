
/*
// 2.2 Implement an algorithm to find the kth to the last element of a singly linked list

#include <iostream>
using namespace std;

template <class T>
class node {
public:
	T value;
	node<T> *next;
public:
	node(T v) : value(v), next(NULL) {}
};

template<class T>
node<T> *find_from_last(node<T> *list, int k) {
	if(!list || (k < 0)) return NULL;
	node<T> *ptr = list;
	node<T> *runner = list;
	for(int i = 0; i < k; i ++) {
		if(runner) runner = runner->next;
		else break;
	}
	if(!runner) return NULL;
	do {
		if(!runner->next) return ptr;
		ptr = ptr->next;
		runner = runner->next;
	} while(true);
	return NULL;
}

template <class T>
node<T> *find_from_last_recursive(node<T> *list, const int k, int *idx) {
	if(!list) {
		*idx = 0;
		return NULL;
	}
	node<T> *item = find_from_last_recursive(list->next, k, idx);
	if(k == (*idx - 1)) return item;
	(*idx) ++;
	return list;
}

template <class T>
void trace(node<T> *list) {
	while(list) {
		cout << list->value << " ";
		list = list->next;
	}
	cout << endl;
}

template <class T>
node<T> *append(node<T> *item, node<T> *list) {
	if(!list) return item;
	node<T> *cur = list;
	while(cur->next) cur = cur->next;
	cur->next = item;
	return list;
}

template <class T>
void release(node<T> *list) {
	while(list) {
		node<T> *cur = list;
		list = list->next;
		delete cur;
	}
}

int main() {
	{
		char test[] = {'a', 'b', 'c', 'd'};
		const int N = sizeof(test);
		node<char> *list = NULL;
		for(int i = 0; i < N; i ++) list = append<char>(new node<char>(test[i]), list);
		trace<char>(list);
		for(int k = 0; k < N; k++) {
			node<char> *n = find_from_last(list, k);
			if(!n) {
				cout << "PROBLEM! NULL" << endl;
				break;
			}
			cout << n->value << endl;
			if(n->value != test[N-1-k]) {
				cout << "PROBLEM! Inequal" << endl;
				break;
			}
		}
		release<char>(list);
	}

	{
		char test[] = {'a', 'b', 'c', 'd'};
		const int N = sizeof(test);
		node<char> *list = NULL;
		for(int i = 0; i < N; i ++) list = append<char>(new node<char>(test[i]), list);
		trace<char>(list);
		for(int k = 0; k < N; k++) {
			int idx = 0;
			node<char> *n = find_from_last_recursive(list, k, &idx);
			if(!n) {
				cout << "PROBLEM! NULL" << endl;
				break;
			}
			cout << n->value << endl;
			if(n->value != test[N-1-k]) {
				cout << "PROBLEM! Inequal" << endl;
				break;
			}
		}
		release<char>(list);
	}
	return 0;
}
*/
