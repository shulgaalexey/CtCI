// 2.1 Write code to remove duplicates from unsorted list.
// FOLLOW UP
// How would you solve this problem if a temporary buffer is not allowed?

#include <iostream>
#include <map>

using namespace std;

template<class T>
class node {
public:
	T value;
	node<T> *next;
public:
	node(T v);
};

template<class T>
node<T>::node(T v) : value(v), next(NULL) {
}

template<class T>
void trace(node<T> *list) {
	while(list) {
		cout << list->value << " ";
		list = list->next;
	}
	cout << endl;
}

template<class T>
void remove_duplicate(node<T> *item, node<T> *list) {
	if(!list || !item) return;
	node<T> *prev = item;
	node<T> *cur = list;
	while(cur) {
		if(cur->value == item->value) {
			prev->next = cur->next;
			delete cur;
			cur = prev->next;
		} else {
			prev = cur;
			cur = cur->next;
		}
	}
}

template<class T>
void remove_duplicates(node<T> *list) {
	if(!list || !list->next) return;
	do {
		remove_duplicate<T>(list, list->next);
		list = list->next;
		if(!list) return;
	} while(true);
}

template<class T>
void remove_duplicates_hash(node<T> *list) {
	if(!list || !list->next) return;
	map<T, bool> m;

	node<T> *prev = list;
	m[prev->value] = true;
	node<T> *cur = list->next;
	while(cur) {
		if(m.count(cur->value) > 0) {
			prev->next = cur->next;
			delete cur;
			if(!prev) return;
			cur = prev->next;
		} else {
			m[cur->value] = true;
			prev = cur;
			cur = cur->next;
		}
	}
}

template<class T>
node<T> *append(node<T> *list, T v) {
	node<T> *item = new node<T>(v);
	if(!list) return item;
	node<T> *cur = list;
	while(cur->next) cur = cur->next;
	cur->next = item;
	return list;
}

template<class T>
void release(node<T> *list) {
	while(list) {
		node<T> *item = list;
		list = list->next;
		delete item;
	}
}

int main() {
	{ // test 1
		node<char> *list = append<char>(NULL, 'a');
		append<char>(list, 'a');
		append<char>(list, 'b');
		append<char>(list, 'a');
		append<char>(list, 'c');
		trace<char>(list);
		remove_duplicates<char>(list);
		trace<char>(list);
		release<char>(list);
		cout << endl;
	}
	{ // test 2
		node<char> *list = append<char>(NULL, 'a');
		append<char>(list, 'b');
		append<char>(list, 'c');
		trace<char>(list);
		remove_duplicates<char>(list);
		trace<char>(list);
		release<char>(list);
		cout << endl;
	}
	{ // test 2
		node<char> *list = append<char>(NULL, 'a');
		append<char>(list, 'a');
		trace<char>(list);
		remove_duplicates<char>(list);
		trace<char>(list);
		release<char>(list);
		cout << endl;
	}

	{ // test 1.hash
			node<char> *list = append<char>(NULL, 'a');
			append<char>(list, 'a');
			append<char>(list, 'b');
			append<char>(list, 'a');
			append<char>(list, 'c');
			trace<char>(list);
			remove_duplicates_hash<char>(list);
			trace<char>(list);
			release<char>(list);
			cout << endl;
		}
		{ // test 2.hash
			node<char> *list = append<char>(NULL, 'a');
			append<char>(list, 'b');
			append<char>(list, 'c');
			trace<char>(list);
			remove_duplicates_hash<char>(list);
			trace<char>(list);
			release<char>(list);
			cout << endl;
		}
		{ // test 3.hash
			node<char> *list = append<char>(NULL, 'a');
			append<char>(list, 'a');
			trace<char>(list);
			remove_duplicates_hash<char>(list);
			trace<char>(list);
			release<char>(list);
			cout << endl;
		}
	return 0;
}
