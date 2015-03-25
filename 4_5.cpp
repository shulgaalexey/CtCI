// 4.5 Implement a function to check if a binary tree is a binary search tree.
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class node {
	public:
		char value;
		node *left;
		node *right;
	public:
		node(char v);
};

static vector<node *> gc; // garbage collector

node::node(char v) : value(v), left(NULL), right(NULL) {
	gc.push_back(this);
}

static void release_gc() {
	for(size_t i = 0; i < gc.size(); i ++ ) delete gc[i];
}

bool is_bst_dfs(node *tree) {
	if(!tree) return true;
	if(tree->left && (tree->left->value > tree->value)) return false;
	if(tree->right && (tree->right->value < tree->value)) return false;
	return is_bst_dfs(tree->left) && is_bst_dfs(tree->right);
}

bool is_bst_bfs(node *tree) {
	if(!tree) return true;
	queue<node *> q;
	q.push(tree);
	while(!q.empty()) {
		node *n = q.front();
		q.pop();
		if(n->left) {
			if(n->left->value > n->value) return false;
			q.push(n->left);
		}
		if(n->right) {
			if(n->right->value < n->value) return false;
			q.push(n->right);
		}
	}
	return true;
}

int main(void) {
	node *n1 = new node(1);
	node *n2 = new node(2);
	node *n3 = new node(3);
	node *n4 = new node(4);
	node *n5 = new node(5);
	node *n6 = new node(6);

	n4->left = n2;
	n4->right = n5;
	n2->left = n1;
	n2->right = n3;
	n6->left = n5;

	///////////////// OK
	//     4
	//  2     6
	// 1 3   5
	/////////////////

	if(!is_bst_dfs(n4)) cout << "PROBLEM!" << endl;
	if(!is_bst_bfs(n4)) cout << "PROBLEM!" << endl;

	n4->right = n5;
	n5->left = n6;
	n6->left = NULL;

	///////////////// FAIL
	//     4
	//  2     5
	// 1 3   6
	/////////////////

	if(is_bst_dfs(n4)) cout << "PROBLEM!" << endl;
	if(is_bst_bfs(n4)) cout << "PROBLEM!" << endl;

	release_gc();
	return 0;
}
