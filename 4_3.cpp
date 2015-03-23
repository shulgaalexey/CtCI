// 4.3 Given a sorted (increasing order) array with nique integer elements,
// write an algorithm to create a binary search tree with minimal length.
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm> // for std::max
#include <map> // for trace
#include <iomanip> // for trace
#include <math.h> // for trace

using namespace std;

class node_pool {
	private:
		vector<class node *> pool;
	public:
		~node_pool();
};

class node {
	public:
		char value;
		node *left;
		node *right;
	public:
		node(char v);
};

node_pool g_pool;

node_pool::~node_pool() {
	for(size_t i = 0; i < pool.size(); i ++) delete pool[i];
	pool.clear();
}

node::node(char v) : value(v), left(NULL), right(NULL) {
}

// 1. Using a queue to create a tree -----------------------
class qitem {
	public:
		int start;
		int finish;
		node *root;
	public:
		qitem(int s, int f) : start(s), finish(f), root(NULL) {}
	public:
		int size() const { return (finish - start + 1); }
		int center() const { return (start + size()/2); }
};

node *create_tree_q(char *arr, const int N) {
	if(N <= 0) return NULL;
	if(N == 1) return new node(arr[0]);

	qitem init(0, N-1);
	init.root = new node(arr[init.center()]);

	queue<qitem> q;
	q.push(init);
	while(!q.empty()) {
		qitem i = q.front();
		q.pop();
		if(i.size() == 2) {
			i.root->left = new node(arr[i.start]);
		} else if(i.size() == 1) {
			continue;
		} else {
			qitem li(i.start, i.center() - 1);
			node *ln = new node(arr[li.center()]);
			li.root = ln;
			i.root->left = ln;
			q.push(li);

			qitem ri(i.center() + 1, i.finish);
			node *rn = new node(arr[ri.center()]);
			ri.root = rn;
			i.root->right = rn;
			q.push(ri);
		}
	}
	return init.root;
}

// 2. Create tree recursively -----------------------------
void perform_create_tree_r(char *arr, const int start, const int finish, node *root) {
	const int size = finish - start + 1;
	const int center = start + size / 2;
	root->value = arr[center];
	if(size == 1) return;
	if(size == 2) {
		root->left = new node(arr[start]);
		return;
	}

	root->left = new node(0);
	perform_create_tree_r(arr, start, center - 1, root->left);

	root->right = new node(0);
	perform_create_tree_r(arr, center + 1, finish, root->right);
}

node *create_tree_r(char *arr, const int N) {
	if(N <= 0) return NULL;
	node *root = new node(0);
	perform_create_tree_r(arr, 0, N-1, root);
	return root;
}

// 3. Create a tree level by level
// (using a queue of items from previous level while generating current level)
node *create_tree_b(char *arr, const int N) {
	if(N <= 0) return NULL;
	int jump = 2;
	int step = 0;
	queue<node *> *level = NULL;
	do {
		int idx = max(0, step * 2 - 1);
		queue<node *> *cur_level = new queue<node *>();
		while(idx < N) {
			node *n = new node(arr[idx]);
			if(level) {
				if(!level->empty()) {
					n->left = level->front();
					level->pop();
				}
				if(!level->empty()) {
					n->right = level->front();
					level->pop();
				}
			}
			cur_level->push(n);
			idx += jump;
		}
		if(level) {
			if(!level->empty()) cout << "error" << endl;
			delete level;
		}
		level = cur_level;
		jump *= 2;
		if(jump > N) break;
		step ++;
	} while(true);
	node *root = level->front();
	level->pop();
	if(!level->empty()) cout << "error2" << endl;
	delete level;
	return root;
}

// Visualize the tree -------------------------------------
size_t get_height(node *tree) {
	if(!tree) return 0;
	return max(get_height(tree->left), get_height(tree->right)) + 1;
}

void print_tree(node *root) {
	const int box_size = 3;
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
			//cout << q.front()->value;
			cout << int(q.front()->value - 'a');
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
}

void trace(node *tree) {
	print_tree(tree);
	cout << endl << endl;
}


// Tests --------------------------------------------------
int main(void) {
	for(int testno = 3; testno < 16; testno ++) {
		vector<char> v;
		for(char i = 0; i< char(testno); i ++) v.push_back('a' + i);
		char *data = v.data();

		node *tq = create_tree_q(data, testno);
		trace(tq);

		node *tr = create_tree_r(data, testno);
		trace(tr);

		//node *tb = create_tree_b(data, testno);
		//trace(tb);
	}

	return 0;
}
