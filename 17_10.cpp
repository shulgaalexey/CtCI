// 17.10
// Encode XML: exchange tag and attribute names with numeric codes
#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

map<string, int> codes;
vector<string> tokens;

bool alfa(const char c) {
	if((c >= 'a') && (c <= 'z'))
		return true;
	if((c >= 'A') && (c <= 'Z'))
		return true;
	if((c >= '0') && (c <= '9'))
		return true;
	return false;
}

void tokenize(const string &s) {
	bool phrase = false;
	char phrase_end = 0;

	for(size_t i = 0; i < s.length(); i ++) {
		const char c = s[i];

		if(phrase) {
			string phr = "";
			while((i < s.length()) && (s[i] != phrase_end))
				phr += s[i ++];
			if(!phr.empty())
				tokens.push_back(phr);
			if(phrase_end != '\"')
				i --;
			phrase = false;
			continue;
		}

		switch(c) {
			case '<': {
					  phrase = false;
					  if(s[i + 1] == '/') {
						  tokens.push_back("</");
						  i ++;
					  } else
						  tokens.push_back("<");
					  break;
				  }
			case '>':
				  phrase = true;
				  phrase_end = '<';
				  tokens.push_back(">");
				  break;
			case '\"':
				  phrase = true;
				  phrase_end = '\"';
				  break;
			default:
				  if(alfa(c)) {
					  string word = "";
					  while((i < s.length()) && alfa(s[i]))
						  word += s[i++];
					  i --;
					  tokens.push_back(word);
				  }
				  break;
		}
	}
}

void encode() {
	bool element_started = false;
	bool tag_started = false;

	for(size_t i = 0; i < tokens.size(); i ++) {
		const string token = tokens[i];
		if(token == "<") {
			element_started = true;
			tag_started = true;
		} else if(token == "</") {
			element_started = false;
		} else if(token == ">") {
			tag_started = false;
			cout << "0 ";
		} else if(!element_started) {
			continue;
		} else {
			if(!tag_started)
				cout << token << " ";
			else {
				if(codes.count(token) > 0)
					cout << codes[token] << " ";
				else
					cout << token << " ";
			}
		}
	}
	cout << endl;
}

int main(void) {
	codes["family"] = 1;
	codes["person"] = 2;
	codes["firstName"] = 3;
	codes["lastName"] = 4;
	codes["state"] = 5;

	const string xml = "<family lastName=\"McDowell\" state=\"CA\">"
		"<person firstName=\"Gayle\">Some Message</person>"
		"</family>";

	tokenize(xml);

	/*cout << "Tokens:" << endl;
	for(size_t i = 0; i < tokens.size(); i ++)
		cout << tokens[i] << endl;
	cout << endl;*/

	encode();

	return 0;
}
