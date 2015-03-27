// 4.8 You have a very large binary trees: T1, with millions of nodes, and T2, with hundreds of nodes.
// Create an algorithm to decide if T2 is a subtree of T1.
// A tree T2 is a subtree of  T1 if there exists a node n in T1 such that the subtree of
// n is identical to T2. That is, if you cut off the tree at node n, the two trees would
// be identical.
#include <iostream>
#include <vector>
#include <queue>
#include <math.h> // for trace
#include <iomanip> // for trace

using namespace std;

vector<class node *> gc;

class node {
	public:
		int value;
		node *left;
		node *right;
	public:
		node() : value(0), left(NULL), right(NULL) {
			static int first_v = 1;
			value = first_v ++;
			gc.push_back(this);
		}
		node(int v) : value(v), left(NULL), right(NULL) {
			gc.push_back(this);
		}
};

void release_gc() {
	for(size_t i = 0; i < gc.size(); i ++) delete gc[i];
}

bool perform_is_subtree(node *T1, node *T2) {
	if(!T2) return true;
	if(T1 != T2) return false;
	return perform_is_subtree(T1->left, T2->left) && perform_is_subtree(T1->right, T2->right);
}

// DFS approach
bool is_subtree(node *T1, node *T2) {
	if(!T1 || !T2) return false;
	if(T1 == T2) {
		if(perform_is_subtree(T1, T2)) return true;
	}
	if(is_subtree(T1->left, T2)) return true;
	if(is_subtree(T1->right, T2)) return true;
	return false;
}

node *gen_tree(node *root, int depth) {
	if(!depth) return NULL;
	root->left = new node();
	root->right = new node();
	gen_tree(root->left, depth - 1);
	gen_tree(root->right, depth - 1);
	return root;
}

// Visualize the tree -------------------------------------
// taken from the internet
size_t get_height(node *tree) {
	if(!tree) return 0;
	return max(get_height(tree->left), get_height(tree->right)) + 1;
}

void print_tree(node *root) {
	const int box_size = 5;
	queue<node *> q;
	q.push(root);
	size_t current_level_nodes = 1;
	size_t next_current_level_nodes = 0;
	size_t level = 1;

	const size_t height = get_height(root);

	int padding = box_size * (pow(2, height - level) - 1);
	cout << setw(padding / 2) << "";
	while (level <= height)
	{
		cout << setw(box_size);
		if (q.front() != NULL)
		{
			cout << q.front()->value;
			q.push(q.front()->left);
			q.push(q.front()->right);
		}
		else
		{
			std::cout << "";
			q.push(NULL);
			q.push(NULL);
		}
		next_current_level_nodes += 2;
		cout << setw(padding) << "";
		q.pop();
		--current_level_nodes;
		if (current_level_nodes == 0)
		{
			current_level_nodes = next_current_level_nodes;
			next_current_level_nodes = 0;
			++level;
			padding = box_size * (pow(2, height - level) - 1);
			cout << "\n" << setw(padding / 2) << "";
		}
	}
	cout << endl << endl;
}


int main(void) {

	node *tree = gen_tree(new node(), 5);

	print_tree(tree);
	print_tree(gc[1]);
	print_tree(gc[19]);

	if(!is_subtree(tree, gc[1])) cout << "PROBLEM!" << endl;
	if(!is_subtree(tree, gc[19])) cout << "PROBLEM!" << endl;
	if(is_subtree(tree, new node())) cout << "PROBLEM!" << endl;

	release_gc();
	return 0;
}
