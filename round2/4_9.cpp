#include <iostream>
#include <vector>
using namespace std;

struct tree {
	int data;
	tree *left;
	tree *right;
	tree(int v) : data(v), left(NULL), right(NULL) {}
};

void print_path(tree *t, const int value, const int level, vector<int> &path) {
	if(!t)
		return;

	if(int(path.size()) < (level + 1))
		path.push_back(t->data);
	else
		path[level] = t->data;

	int sum = 0;
	for(int i = level; i >= 0; i --) {
		sum += path[i];
		if(sum == value) {
			for(int j = i; j <= level; j ++) {
				cout << path[j] << " ";
			}
			cout << endl;
		}
	}

	print_path(t->left, value, level + 1, path);
	print_path(t->right, value, level + 1, path);
}

int main(void) {
	tree *n1 = new tree(1);
	tree *n2 = new tree(2);
	tree *n3 = new tree(3);
	tree *n4 = new tree(4);
	tree *n5 = new tree(5);
	tree *n6 = new tree(6);
	tree *n7 = new tree(7);
	tree *n8 = new tree(8);
	tree *n9 = new tree(9);
	tree *n10 = new tree(10);
	tree *n11 = new tree(11);
	tree *n12 = new tree(12);
	tree *n13 = new tree(13);
	tree *n14 = new tree(14);
	tree *n15 = new tree(15);

	n1->left = n2;
	n1->right = n3;
	n2->left = n4;
	n2->right = n5;
	n4->left = n8;
	n4->right = n9;
	n5->left = n10;
	n5->right = n11;
	n3->left = n6;
	n3->right = n7;
	n6->left = n12;
	n6->right = n13;
	n7->left = n14;
	n7->right = n15;

	vector<int> path;
	print_path(n1, 18, 0, path);

	return 0;
}
