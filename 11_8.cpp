// 11.8 Imaging you are reading in a stream of integers. Periodically, you wish
// to be able to look up the rank of a number x (the number of values less than
// or equal to x).
// Implement a data structure and algorithm to support these operations. That
// is, implement the method track(int x), which is called when each number is
// generated, and the method getRangeOfNumber(int x), which returns the number
// of values less than or equal to x (not including x itself).
// EXAMPLE
// Stream (in order of appearance): 5, 1, 4, 4, 5, 9, 7, 13, 3
// getRankOfNumber(1) = 0;
// getRankOfNumber(3) = 1;
// getRankOfNumber(4) = 3;

#include <iostream>
using namespace std;

class ranked_stream {
	class node {
	public:
		int val;
		int cnt;
		node *left;
		node *right;
	public:
		node(int v) : val(v), cnt(0), left(NULL), right(NULL) {}
		~node() {}
	};


public:
	node *tree;
	int min;
	int max;
	int size;
public:
	ranked_stream();
	~ranked_stream();
public:
	void track(int x);
	int getRankOfNumber(int x);
private:
	void insert(node *root, int v);
	void count_rank(node *root, int v, int *cnt);
	void release(node *root);
};

ranked_stream::ranked_stream()
	: tree(NULL)
	  , min(0)
	  , max(0)
	  , size(0)
{
}

ranked_stream::~ranked_stream() {
	release(tree);
}

void ranked_stream::release(node *root) {
	if(!root)
		return;
	release(root->left);
	release(root->right);
	delete root;
}

void ranked_stream::track(int x) {
	if(!tree) {
		size = 0;
		min = x;
		max = x;
		tree = new node(x);
	} else {
		size ++;
		if(x < min)
			min = x;
		if(x > max)
			max = x;
		insert(tree, x);
	}
}

int ranked_stream::getRankOfNumber(int x) {
	if((size == 0) || (x < min) || (x > max))
		return -1;
	int cnt = 0;
	count_rank(tree, x, &cnt);
	return cnt;
}

void ranked_stream::insert(node *root, int v) {
	if(!root)
		return;
	if(v <= root->val) {
		root->cnt ++;
		if(root->left)
			insert(root->left, v);
		else
			root->left = new node(v);
	} else {
		if(root->right)
			insert(root->right, v);
		else
			root->right = new node(v);
	}
}

void ranked_stream::count_rank(node *root, int v, int *cnt) {
	if(!root)
		return;
	if(v < root->val) {
		count_rank(root->left, v, cnt);
	} else if(v == root->val) {
		*cnt += root->cnt;
		return;
	} else {
		*cnt += root->cnt + 1;
		count_rank(root->right, v, cnt);
	}
}

int main(void) {
	{ //1
		ranked_stream s;
		int a[] = {5, 1, 4, 4, 5, 9, 7, 13, 3};
		for(int i = 0; i < int(sizeof(a) / sizeof(a[0])); i ++)
			s.track(a[i]);

		if(s.getRankOfNumber(1) != 0)
			cout << "ERROR_1_1" << endl;

		if(s.getRankOfNumber(3) != 1)
			cout << "ERROR_1_2" << endl;

		if(s.getRankOfNumber(4) != 3)
			cout << "ERROR_1_3" << endl;
	}

	{ //2
		ranked_stream s;
		int a[] = {5, 10, 13, 15, 20, 23, 24, 25};
		for(int i = 0; i < int(sizeof(a) / sizeof(a[0])); i ++)
			s.track(a[i]);

		if(s.getRankOfNumber(5) != 0)
			cout << "ERROR_2_1" << endl;

		if(s.getRankOfNumber(10) != 1)
			cout << "ERROR_2_2" << endl;

		if(s.getRankOfNumber(13) != 2)
			cout << "ERROR_2_3" << endl;

		if(s.getRankOfNumber(15) != 3)
			cout << "ERROR_2_4" << endl;

		if(s.getRankOfNumber(20) != 4)
			cout << "ERROR_2_5" << endl;

		if(s.getRankOfNumber(22) != 5)
			cout << "ERROR_2_6" << endl;

		if(s.getRankOfNumber(23) != 5)
			cout << "ERROR_2_7" << endl;

		if(s.getRankOfNumber(24) != 6)
			cout << "ERROR_2_8" << endl;

		if(s.getRankOfNumber(25) != 7)
			cout << "ERROR_2_9" << endl;
	}

	cout << "OK" << endl;

	return 0;
}
