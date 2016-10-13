#include <iostream>
#include <climits>
using namespace std;

struct tree {
	int data;
	tree *left;
	tree *right;
	tree(int v) : data(v), left(NULL), right(NULL) {}
};

bool within_range(int a, int min, int max) {
	return ((a >= min) && (a <= max));
}

bool is_bst(tree *t, int min, int max) {
	if(!t)
		return true;

	if(!within_range(t->data, min, max))
		return false;

	if(t->left && (t->left->data > t->data))
		return false;
	if(t->right && (t->right->data <= t->data))
		return false;

	return is_bst(t->left, min, t->data) && is_bst(t->right, t->data, max);
}

int main(void) {
	{ // 1 and 2
		tree *t0 = new tree(0);
		tree *t1 = new tree(1);
		tree *t2 = new tree(2);
		tree *t3 = new tree(3);
		tree *t4 = new tree(4);
		tree *t5 = new tree(5);
		tree *t6 = new tree(6);

		t3->left = t1;
		t3->right = t5;
		t1->right = t2;
		t5->left = t4;

		if(!is_bst(t3, INT_MIN, INT_MAX))
			cout << "ERROR1" << endl;

		t1->left = t0;
		t5->right = t6;

		if(!is_bst(t3, INT_MIN, INT_MAX))
			cout << "ERROR2" << endl;

	}

	{ // 3
		tree *t0 = new tree(0);
		tree *t1 = new tree(1);
		tree *t2 = new tree(2);
		tree *t3 = new tree(3);
		tree *t4 = new tree(4);
		tree *t5 = new tree(5);
		tree *t6 = new tree(6);

		t3->left = t1;
		t3->right = t5;
		t1->left = t2;
		t1->left = t0;
		t5->right = t4; // ERROR
		t5->left = t6; // ERROR

		if(is_bst(t3, INT_MIN, INT_MAX))
			cout << "ERROR3" << endl;
	}
	return 0;
}
