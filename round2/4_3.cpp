#include <iostream>
using namespace std;

struct tree {
	int data;
	tree *left;
	tree *right;
	tree(int v) : data(v), left(NULL), right(NULL) {}
};

tree *build_binary_search_tree(int *arr, int start, int finish) {
	if((start < 0) || (start > finish))
		return NULL; // empty leave
	if(start == finish)
		return new tree(arr[start]); // valid leave

	const int mid = int((start + finish) / 2);
	tree *n = new tree(arr[mid]);
	n->left = build_binary_search_tree(arr, start, mid - 1);
	n->right = build_binary_search_tree(arr, mid + 1, finish);
	return n;
}

void trace(tree *t) {
	if(!t) return;

	cout << t->data << " ";
	if(t->left)
		cout << " l: " << t->left->data;
	if(t->right)
		cout << " r: " << t->right->data;
	cout << endl;

	trace(t->left);
	trace(t->right);
}

int main(void) {

	{ // 1
		int arr[] = {0, 1, 2, 3, 4, 5, 6};
		int size = int(sizeof(arr) / sizeof(arr[0]));
		tree *t = build_binary_search_tree(arr, 0, size - 1);
		trace(t);
		cout << endl;
	}

	{ // 2
		int arr[] = {0, 1, 2, 3, 4};
		int size = int(sizeof(arr) / sizeof(arr[0]));
		tree *t = build_binary_search_tree(arr, 0, size - 1);
		trace(t);
		cout << endl;
	}

	{ // 3
		int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
		int size = int(sizeof(arr) / sizeof(arr[0]));
		tree *t = build_binary_search_tree(arr, 0, size - 1);
		trace(t);
		cout << endl;
	}


	return 0;
}
