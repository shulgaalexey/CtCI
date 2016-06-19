// 18.10 Given two words of equal length that are in a dictionary, write a
// method to transform one word into another word by changing only one letter at
// a time. The new word you get in each step must be in the dictionary.
// EXAMPLE
// Input: DAMP, LIKE
// Output: DAMP -> LAMP -> LIME -> LIKE
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
using namespace std;

vector<string> generate_words(const string &w) {
	vector<string> ret;
	for(size_t i = 0; i < w.length(); i ++) {
		const char cur = w[i];
		for(char c = 'A'; c <= 'Z'; c ++) {
			if(c == cur)
				continue;
			string v = w;
			v[i] = c;
			ret.push_back(v);
		}
	}
	return ret;
}

map<string, bool> dictionary;

vector<string> find_path(const string &start_word, const string &end_word) {
	queue<string> q;
	map<string, string> bt; // back-tracking
	map<string, bool> visited;

	q.push(start_word);
	visited[start_word] = true;

	while(!q.empty()) {
		string w = q.front();
		q.pop();
		vector<string> words = generate_words(w);
		for(size_t i = 0; i < words.size(); i ++) {
			const string v = words[i];
			if(v == end_word) {
				vector<string> ret;
				//ret.push_back(v);
				ret.insert(ret.begin(), v);
				while(true) {
					//ret.push_back(w);
					ret.insert(ret.begin(), w);
					if(bt.count(w) <= 0)
						break;
					w = bt[w];
				}
				return ret;
			}

			if(dictionary.count(v) <= 0)
				continue; // no such word in dictionary

			if(visited.count(v) > 0)
				continue; // already visited

			q.push(v);
			visited[v] = true;
			bt[v] = w;
		}
	}

	vector<string> empty;
	return empty;
}

int main(void) {
	dictionary["DAMP"] = true;
	dictionary["LAMP"] = true;
	dictionary["LIKE"] = true;
	dictionary["LIME"] = true;
	dictionary["LIMP"] = true;

	vector<string> path = find_path("DAMP", "LIKE");

	cout << "DAMP, LIKE:" << endl;
	for(size_t i = 0; i < path.size(); i++) {
		cout << path[i];
		if((i + 1) < path.size())
			cout << " -> ";
	}
	cout << endl;

	return 0;
}
