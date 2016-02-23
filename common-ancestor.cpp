// Finding common ancestor of two nodes in the tree
#include <iostream>
using namespace std;

struct node { int p, l, r; };

static const node empty_node = { -1, -1, -1 };

int get_size(node *tree, int n) {
	if(n == (-1))
		return 0;
	return (1 + get_size(tree, tree[n].l) + get_size(tree, tree[n].r));
}

int find_common_ancestor(node *tree, int const N, int n1, int n2, int *ancestor) {
	bool visited[N];
	for(int i = 0; i < N; i ++)
		visited[i] = false;

	// move top from n1
	int cur = n1;
	while(true) {
		visited[cur] = true;
		cur = tree[cur].p;
		if(cur == (-1))
			break;
	}

	// move top from n2
	cur = n2;
	while(true) {
		if(visited[cur]) {
			*ancestor = cur;
			break;
		}
		visited[cur] = true;
		cur = tree[cur].p;
		if(cur == (-1))
			return -1;
	}

	return get_size(tree, *ancestor);
}


int main(void) {
	{ // 1
		const int N = 13;
		int v[] = {1, 2, 1, 3, 2, 4, 3, 5, 3, 6, 4, 7, 7, 12, 5, 9, 5,
			8, 6, 10, 6, 11, 11, 13};

		node tree[N];
		for(int i = 0; i < N; i ++)
			tree[i] = empty_node;
		for(int i = 0; i < int(sizeof(v) / sizeof(v[0])); i ++) {
			int p = v[i] - 1;
			i ++;
			int n = v[i] - 1;
			if(tree[p].l == (-1))
				tree[p].l = n;
			else
				tree[p].r = n;

			tree[n].p = p;
		}

		int ancestor = -1;
		int size = find_common_ancestor(tree, N, 7, 12, &ancestor);
		cout << "ancestor: " << (ancestor + 1)  << endl;
		cout << "size: " << size << endl;
	}

	{ // 1
		const int N = 10;
		int v[] = {1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10};

		node tree[N];
		for(int i = 0; i < N; i ++)
			tree[i] = empty_node;
		for(int i = 0; i < int(sizeof(v) / sizeof(v[0])); i ++) {
			int p = v[i] - 1;
			i ++;
			int n = v[i] - 1;
			if(tree[p].l == (-1))
				tree[p].l = n;
			else
				tree[p].r = n;

			tree[n].p = p;
		}

		int ancestor = -1;
		int size = find_common_ancestor(tree, N, 0, 9, &ancestor);
		cout << "ancestor: " << (ancestor + 1)  << endl;
		cout << "size: " << size << endl;
	}

	return 0;
}
