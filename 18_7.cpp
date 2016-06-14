// 18.7 Given a list of words, write a program to find the longest word made of
// other words in the list.
// EXAMPLE
// Input: cat banana, dog, nana, walk, walker, dogwalker
// Output: dogwalker
#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

map<string, string> _m;

bool is_word_composite(const string &w, bool original_word) {
	if(!original_word && (_m.count(w) > 0))
		return true;

	for(size_t i = 0; i < w.length(); i ++) {
		const string w1 = w.substr(0, i);
		const string w2 = w.substr(i);
		if(is_word_composite(w1, false)
				&& is_word_composite(w2, false)) {
			_m[w1] = w1;
			_m[w2] = w2;
			return true;
		}
	}
	return false;
}

string find_longest_composite(const vector<string> &words) {
	_m.clear();
	for(size_t i = 0; i < words.size(); i ++)
		_m[words[i]] = words[i];

	string longest;
	for(size_t i = 0; i < words.size(); i ++)
		if(is_word_composite(words[i], true) && (words[i].length() > longest.length()))
			longest = words[i];

	return longest;
}

int main(void) {
	{ // 1
		vector<string> words;
		words.push_back("cat");
		words.push_back("banana");
		words.push_back("dog");
		words.push_back("nana");
		words.push_back("walk");
		words.push_back("walker");
		words.push_back("dogwalker");

		const string longest = find_longest_composite(words);
		cout << longest << endl;
		if(longest != "dogwalker")
			cout << "ERROR" << endl;
	}

	{ // 2
		vector<string> words;
		words.push_back("aa");
		words.push_back("bb");
		words.push_back("cc");
		words.push_back("dd");
		words.push_back("ee");
		words.push_back("ff");
		words.push_back("aacc");
		words.push_back("bbccdd");
		words.push_back("aaccklm");

		const string longest = find_longest_composite(words);
		cout << longest << endl;
		if(longest != "bbccdd")
			cout << "ERROR" << endl;
	}


	return 0;
}
