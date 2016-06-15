// 18.8 Given a string s and an array of smaller strings T, design a method to
// search s for each small string in T.
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class SuffixTreeNode {
	map<char, SuffixTreeNode *> children;
	char value;
	vector<int> indexes;
	public:
	void insertString(const string &s, int index) {
		indexes.push_back(index);
		if(s.empty())
			return;
		value = s[0];
		SuffixTreeNode *child = NULL;
		if(children.count(value) > 0)
			child = children[value];
		else {
			child = new SuffixTreeNode;
			children[value] = child;
		}
		const string remainder = s.substr(1);
		child->insertString(remainder, index);
	}

	vector<int> search(const string &s) {
		if(s.empty())
			return indexes;
		char first = s[0];
		if(children.count(first) > 0) {
			const string remainder = s.substr(1);
			return children[first]->search(remainder);
		}
		return vector<int>();
	}
};

class SuffixTree {
	SuffixTreeNode root;
	public:
	SuffixTree(const string &s) {
		for(int i = 0; i < int(s.length()); i ++) {
			string suffix = s.substr(i);
			root.insertString(suffix, i);
		}
	}

	vector<int> search(const string &s) {
		return root.search(s);
	}
};

int main(void) {
	{ // 1
		SuffixTree st("bibs");
		vector<int> ret = st.search("b");
		for(size_t i = 0; i < ret.size(); i ++)
			cout << ret[i] << " ";
		cout << endl;
	}

	{ // 2
		SuffixTree st("baaccceeeffa");
		vector<int> ret = st.search("cc");
		for(size_t i = 0; i < ret.size(); i ++)
			cout << ret[i] << " ";
		cout << endl;
	}

	return 0;
}
