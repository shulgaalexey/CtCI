// 4.9 You are gven a binary tree in which each node contains a value.
// Design an algorithm to print all paths which sum to a given value.
// The path does not need to start or end at the root or a leaf, but it must go in a straight line down.
#include <iostream>
#include <algorithm>
using namespace std;

class node {
	public:
		int value;
		node *left;
		node *right;
	public:
		node() : value(0), left(NULL), right(NULL) {}
		node(int v) : value(v), left(NULL), right(NULL) {}
		void set_children(node *l, node *r) {
			left = l;
			right = r;
		}
};

int get_depth(node *tree) {
	if(!tree) return 0;
	return max(get_depth(tree->left), get_depth(tree->right)) + 1;
}

void print_cur_path(int *path, const int start, const int size) {
	for(int i = start; i < size; i ++) cout << path[i] << " ";
	cout << endl;
}

void perform_print_paths(node *tree, const int sum, int *path, const int level) {
	if(!tree) return;
	path[level] = tree->value;
	int cur_sum = 0;
	for(int i = level; i >= 0; i--) {
		cur_sum += path[i];
		if(cur_sum == sum)
			print_cur_path(path, i, level + 1);
	}
	perform_print_paths(tree->left, sum, path, level + 1);
	perform_print_paths(tree->right, sum, path, level + 1);
}

void print_paths(node *tree, const int sum) {
	if(!tree) return;
	const int depth = get_depth(tree);
	int *path = new int[depth];
	perform_print_paths(tree, sum, path, 0);
	delete [] path;
}

int main(void) {

	////////////////////////////////////////////
	//
	//                     3
	//           2                    8
	//     2         4          0         9
	//  6    3    1    -2    5    -4    7    6
	//
	////////////////////////////////////////////

	node *n = new node[15];

	n[0] = 3;
	n[1] = 2;
	n[2] = 8;
	n[3] = 2;
	n[4] = 4;
	n[5] = 0;
	n[6] = 9;
	n[7] = 6;
	n[8] = 3;
	n[9] = 1;
	n[10] = -2;
	n[11] = 5;
	n[12] = -4;
	n[13] = 7;
	n[14] = 6;

	n[0].set_children(&n[1], &n[2]);
	n[1].set_children(&n[3], &n[4]);
	n[2].set_children(&n[5], &n[6]);
	n[3].set_children(&n[7], &n[8]);
	n[4].set_children(&n[9], &n[10]);
	n[5].set_children(&n[11], &n[12]);
	n[6].set_children(&n[13], &n[14]);

	print_paths(&n[0], 7);

	delete [] n;
	return 0;
}
