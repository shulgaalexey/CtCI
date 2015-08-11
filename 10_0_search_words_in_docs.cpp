// Given a list of millions of documents, how would you find all documents that
// contain a list of words? The words do not need to appear in any particular
// order,  but they must be complete words. That is, "book" does not match
// "bookkeeper".
//
// My naive solution (from the memory):
//  * Preprocess the Data Base
//    * In each document prepare a glossary - a table, containing all words from this doc
//    * Prepare Inversed Index - table where one collumn is a word, and another is a list of doc names
//      where this word was met (something like BigTable)
//
//  * Find the given list of words in all documents, use one of following approaches:
//    * Trivial approach - get the doc, check if all words are there, add it to
//      the resulting list
//      (pros: may be parrallelized such as map-reduce,
//      cons: to get result we must wait until all docs in
//      each parallel job  are  processed)
//    * Iterative relevance approach - for each word, add docs including this word to the temporary table;
//      increase the score of the doc for every searching word; return docs,
//      which score equals the numbe of searched words
//      (pros: may be nice in usecases, where the search is halted somewhere in the middle and we can have
//      a list of docs which are potential candidates to be a result of search query, also we will have the
//      relevance score for each doc;
//      cons: need too many memory to store that candidates)
//    * Exclusive approach - generate a list of docs, including the first word from the list;
//      for each next word, get the list of docs, including it and intersect
//      with that first list, reducing this way the first list
//      (pros: may be nice in usecases, where the search is halted somewhere in the middle and we can have a
//      list of docs which are potential candidates to be a result of search query;
//      cons: need too many memory to store that candidates)

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
using namespace std;


//-----------------------------------------------------------------------------
// Data Model
//-----------------------------------------------------------------------------

// Document data structure
class doc {
	public:
		string name;
		string content;
		map<string, int> glossary;
	public:
		doc() {}
		doc(const string &n, const string &c) : name(n), content(c) {}
};


vector<doc> _docs;	// Base of documents

map<string, vector<string> > _iit; // Inversed Index Table

//-----------------------------------------------------------------------------
// Data Base Preprocessing
//-----------------------------------------------------------------------------

// Generate a glossary on the base of content
void gen_glossary(const string &content, map<string, int> &glossary) {
	istringstream iss(content);
	string word;
	while(iss >> word) {
		if(glossary.count(word) <= 0)
			glossary[word] = 0;
		glossary[word] ++;
	}
}

// Preprocess docs by preparing their glossaries
void preprocess_docs() {
	for(size_t i = 0; i < _docs.size(); i ++)
		gen_glossary(_docs[i].content, _docs[i].glossary);
}

void gen_iit() {
	for(size_t i = 0; i < _docs.size(); i ++) {
		doc &d = _docs[i];
		for(map<string, int>::iterator it = d.glossary.begin(); it != d.glossary.end(); ++it) {
			const string word = it->first;
			if(_iit.count(word) <= 0)
				_iit[word] = vector<string>();
			_iit[word].push_back(d.name);
		}
	}
}

void preprocess_data_base() {
	// Clear the DB
	for(size_t i = 0; i < _docs.size(); i ++)
		_docs[i].glossary.clear();
	_iit.clear();

	// Preprocess the DB
	preprocess_docs();
	gen_iit();
}


//-----------------------------------------------------------------------------
// Data Base Querring
//-----------------------------------------------------------------------------

// Sequentally search documents one-by-one
vector<string> find_docs_sequentally(const vector<string> &words) {
	vector<string> results;

	// Check if all words exist in the index
	for(size_t i = 0; i < words.size(); i ++)
		if(_iit.count(words[i]) <= 0)
			return results;

	// Select docs containing given words
	for(size_t d = 0; d < _docs.size(); d ++) {
		bool ok = true;
		for(size_t w = 0; w < words.size(); w ++) {
			if(_docs[d].glossary.count(words[w]) <= 0) {
				ok = false;
				break;
			}
		}
		if(ok)
			results.push_back(_docs[d].name);
	}
	return results;
}

// Exclusively update list of resulting docs while iterating through searched
// words
vector<string> find_docs_exclusively(const vector<string> &words) {
	vector<string> results;

	// Check if all words exist in the index
	for(size_t i = 0; i < words.size(); i ++)
		if(_iit.count(words[i]) <= 0)
			return results;

	// Select docs containing given words
	map<string, int> cur_docs;
	for(size_t i = 0; i < words.size(); i ++) {
		const string word = words[i];
		vector<string> &docs = _iit[word];
		if(i == 0) { // Initially add all docs, containing the first word
			for(size_t d = 0; d < docs.size(); d ++) {
				cur_docs[docs[d]] = 1;
			}
		} else {
			map<string, int> tmp_docs;
			for(size_t d = 0; d < docs.size(); d ++) {
				if(cur_docs.count(docs[d]) > 0)
					tmp_docs[docs[d]] = 1;
			}
			cur_docs = tmp_docs;
		}
	}

	for(map<string, int>::iterator it = cur_docs.begin(); it != cur_docs.end(); ++it)
		results.push_back(it->first);

	return results;
}

// Update list of resulting docs by frequency of words
vector<string> find_docs_by_relevance(const vector<string> &words) {

	vector<string> results;

	// Check if all words exist in the index
	for(size_t i = 0; i < words.size(); i ++)
		if(_iit.count(words[i]) <= 0)
			return results;

	// For docs containing given words update their relevance score
	map<string, int> cur_docs;
	const size_t N = words.size();
	for(size_t i = 0; i < N; i ++) {
		const string word = words[i];
		vector<string> &docs = _iit[word];
		for(size_t d = 0; d < docs.size(); d ++) {
			if(cur_docs.count(docs[d]) <= 0)
				cur_docs[docs[d]] = 0;
			cur_docs[docs[d]] ++;	// Increase doc relevance score
		}
	}

	// Extrace docs with relevance score equal number of words
	for(map<string, int>::iterator it = cur_docs.begin(); it != cur_docs.end(); ++ it) {
		if(size_t(it->second) == N)
			results.push_back(it->first);
	}

	return results;
}


//-----------------------------------------------------------------------------
// Tests
//-----------------------------------------------------------------------------

map<string, int> list2map(const vector<string> &v) {
	map<string, int> m;
	for(size_t i = 0; i < v.size(); i ++)
		m[v[i]] = 0;
	return m;
}

bool lists_equal(const vector<string> &v1, const vector<string> &v2) {
	if(v1.size() != v2.size())
		return false;

	map<string, int> m1 = list2map(v1);
	for(size_t i = 0; i < v2.size(); i ++)
		if(m1.count(v2[i]) <= 0)
			return false;

	return true;
}

int main(void) {
	_docs.push_back(doc("a.txt", "NOSE ARM REGENERATION ANT TERMIT"));
	_docs.push_back(doc("a-.txt", "NOSE REGENERATION ANT TERMIT")); // Not all key words are there
	_docs.push_back(doc("a--.txt", "ROSE ARK DEGENERATION ART TARGET")); // No key words are there
	_docs.push_back(doc("b.txt", "NOSE ARM REGENERATION ANT TERMIT . "
				"Depending on the location context, the number of relevANT places might "
				"be large. Therefore this query may not only return places, but also "
				"suggestions for additional filter criteria that allow users to "
				"interactively refine the classes of places they are interested in."));
	_docs.push_back(doc("c.txt", "Optionally, you __ REGENERATION _ can set the maximum "
				"amount of search results and a default country code "
				"using the maps_preference_set_max_results() and _ NOSE _ "
				"maps_preference_set_country_code() functions respectively. "
				"To set specific _ ARM _ preferences for the map provider, use "
				"the maps_preference_set_property() function with key-value pairs, "
				"defined in the appropriate map provider _ ANT ___documentation. "
				"To get the _ and _ preferences currently applied in the "
				"map _ TERMIT _  provider, use the following functions:"));

	preprocess_data_base();

	vector<string> words;
	words.push_back("NOSE");
	words.push_back("ARM");
	words.push_back("REGENERATION");
	words.push_back("ANT");
	words.push_back("TERMIT");


	vector<string> v1 = find_docs_sequentally(words);
	vector<string> v2 = find_docs_exclusively(words);
	vector<string> v3 = find_docs_by_relevance(words);

	/*cout << "Sequentally" << endl;
	for(size_t i = 0; i < v1.size(); i ++) cout << " " << v1[i]; cout << endl;
	cout << "Exclusively" << endl;
	for(size_t i = 0; i < v2.size(); i ++) cout << " " << v2[i]; cout << endl;
	cout << "By relevance" << endl;
	for(size_t i = 0; i < v3.size(); i ++) cout << " " << v3[i]; cout << endl;*/

	vector<string> expected;
	expected.push_back("a.txt");
	expected.push_back("b.txt");
	expected.push_back("c.txt");

	if(!lists_equal(v1, expected)) cout << "ERROR!" << endl;
	if(!lists_equal(v2, expected)) cout << "ERROR!" << endl;
	if(!lists_equal(v3, expected)) cout << "ERROR!" << endl;

	return 0;
}
