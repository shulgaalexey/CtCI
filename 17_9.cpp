// 17.9 Design a method to find the frequency of occurrence of any given
// word in a book.
#include <iostream>
#include <sstream>
#include <map>
#include <locale>
#include <algorithm>
using namespace std;

map<string, int> _m;

void pre_process(const string &s) {
	_m.clear();

	istringstream iss(s);
	string word;
	locale loc;
	char punct[] = {',', '.', ':', ';', '!', '?'};
	while(iss >> word) {

		// Convert all chars to lower case
		for(size_t i = 0; i < word.length(); i++)
			word[i] = tolower(word[i], loc);

		// Remove punctuation
		for(int i = 0; i < int(sizeof(punct) / sizeof(punct[9])); i ++)
			word.erase(remove(word.begin(), word.end(), punct[i]),
				word.end());

		// Index the word
		if(_m.count(word) > 0)
			_m[word] ++;
		else
			_m[word] = 1;
	}
}

int get_freq(const string &word) {
	string w = word;
	locale loc;
	for(size_t i = 0; i < word.length(); i++)
		w[i] = tolower(word[i], loc);
	if(_m.count(w) > 0)
		return _m[w];
	else
		return 0;
}

int main(void) {
	const string s = "Maps are associative containers that store elements "
		"formed by a combination of a key value and a mapped value, "
		"following a specific order. In a map, the key values are "
		"generally used to sort and uniquely identify the elements, "
		"while the mapped values store the content associated to this "
		"key. The types of key and mapped value may differ, and are "
		"grouped together in member type value_type, which is a pair "
		"type combining both.";

	pre_process(s);

	if(get_freq("maps") != 1)
		cout << "Error1" << endl;
	if(get_freq("type") != 2)
		cout << "Error2" << endl;
	if(get_freq("ARE") != 3)
		cout << "Error3" << endl;

	/*istringstream iss(s);
	string word;
	int words = 0;
	while(iss >> word) {
		words ++;
		cout << word << ": " << get_freq(word) << endl;
	}
	cout << "_______________________" << endl;
	cout << "Words processed: " << words << endl;*/


	int words = 0;
	for(map<string, int>::iterator it = _m.begin(); it != _m.end(); ++it) {
		cout << it->first << ": " << it->second << endl;
		words ++;
	}
	cout << "_______________________" << endl;
	cout << "Words found: " << words << endl << endl;

	return 0;
}
