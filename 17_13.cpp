// 17.13
#include <iostream>
#include <utility>

using namespace std;

class BiNode {
	public:
		BiNode *left;
		BiNode *right;
		int data;
	public:
		BiNode(int d) :
			left(NULL), right(NULL), data(d) {}
};

pair<BiNode *, BiNode *> convert(BiNode *root) {
	if(!root)
		return pair<BiNode *, BiNode *>(NULL, NULL);

	pair<BiNode *, BiNode *> left_list;
	if(root->left) {
		left_list = convert(root->left);
		left_list.second->right = root;
		root->left = left_list.second;
	} else {
		left_list.first = root;
		left_list.second = root;
	}

	pair<BiNode *, BiNode *> right_list;
	if(root->right) {
		right_list = convert(root->right);
		right_list.first->left = root;
		root->right = right_list.first;
	} else {
		right_list.first = root;
		right_list.second = root;
	}

	return pair<BiNode *, BiNode *>(left_list.first, right_list.second);
}

int main(void) {
	{ // 1
		BiNode *pool[7] = {0};
		for(int i = 0; i < 7; i ++)
			pool[i] = new BiNode(i);


		pool[4]->left = pool[2];
		pool[4]->right = pool[5];

		pool[2]->left = pool[1];
		pool[2]->right = pool[3];

		pool[1]->left = pool[0];

		pool[5]->right = pool[6];

		convert(pool[4]);

		int cnt = 0;
		BiNode *head = pool[0];
		while(head) {
			cout << head->data << " ";
			if(head->data != cnt)
				cout << "<-E ";
			head = head->right;
			cnt ++;
		}
		cout << endl;

		cnt = 6;
		BiNode *tail = pool[6];
		while(tail) {
			cout << tail->data << " ";
			if(tail->data != cnt)
				cout << "<-E ";
			tail = tail->left;
			cnt --;
		}
		cout << endl;

		for(int i = 0; i < 7; i ++)
			delete pool[i];
	}


	{ // 2
		BiNode *pool[16] = {0};
		for(int i = 0; i < 16; i ++)
			pool[i] = new BiNode(i);


		pool[8]->left = pool[4];
		pool[8]->right = pool[12];

		pool[4]->left = pool[2];
		pool[4]->right = pool[6];

		pool[2]->left = pool[1];
		pool[2]->right = pool[3];

		pool[1]->left = pool[0];

		pool[6]->left = pool[5];
		pool[6]->right = pool[7];

		pool[12]->left = pool[10];
		pool[12]->right = pool[14];

		pool[10]->left = pool[9];
		pool[10]->right = pool[11];

		pool[14]->left = pool[13];
		pool[14]->right = pool[15];

		convert(pool[8]);


		int cnt = 0;
		BiNode *head = pool[0];
		while(head) {
			cout << head->data << " ";
			if(head->data != cnt)
				cout << "<-E ";
			head = head->right;
			cnt ++;
		}
		cout << endl;

		cnt = 15;
		BiNode *tail = pool[15];
		while(tail) {
			cout << tail->data << " ";
			if(tail->data != cnt)
				cout << "<-E ";
			tail = tail->left;
			cnt --;
		}
		cout << endl;

		for(int i = 0; i < 16; i ++)
			delete pool[i];
	}

	return 0;
}
