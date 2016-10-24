#include <iostream>
using namespace std;

struct tree {
	tree *left;
	tree *right;
	int data;
	int cnt;
	tree(int d) : left(NULL), right(NULL), data(d), cnt(0) {}
};

void track(tree *t, int d) {
	if(!t)
		return;
	if(d <= t->data) {
		if(!t->left)
			t->left = new tree(d);
		else
			track(t->left, d);
		t->cnt ++;
	} else {
		if(!t->right)
			t->right = new tree(d);
		else
			track(t->right, d);
	}
}

int rank(tree *t, int d) {
	if(d == t->data)
		return t->cnt;
	else if(d < t->data) {
		if(!t->left)
			return -1;
		else
			return rank(t->left, d);
	} else {
		int rr = (t->right) ? rank(t->right, d) : (-1);
		if(rr == (-1))
			return -1;
		else
			return t->cnt + 1 + rr;
	}
}

int main(void) {

	int arr[] = {5, 1, 4, 4, 5, 9, 7, 13, 2};

	tree *t = new tree(5);
	for(int i = 1; i < int(sizeof(arr) / sizeof(arr[0])); i ++)
		track(t, arr[i]);

	cout << rank(t, 1) << endl; // 0
	cout << rank(t, 3) << endl; // 1
	cout << rank(t, 4) << endl; // 3

	return 0;
}
