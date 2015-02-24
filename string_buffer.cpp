#include <iostream>
#include <vector>
#include <string>
using namespace std;

class string_buffer {
	vector<string> buffer;
public:
	void add(const string &s);
	string to_string() const;
};

void string_buffer::add(const string &s) {
	buffer.push_back(s);
}

string string_buffer::to_string() const {
	int total_length = 0;
	for(int i = 0; i < int(buffer.size()); i ++) {
		total_length += buffer[i].length();
	}

	string ret(total_length, 0);
	int cur_position = 0;
	for(int i = 0; i < int(buffer.size()); i ++) {
		ret.replace(cur_position, buffer[i].length(), buffer[i].c_str());
		cur_position += buffer[i].length();
	}
	return ret;
}

int main() {
	string_buffer b;
	b.add("one");
	b.add("two");
	b.add("three");

	const string s = b.to_string();
	cout << s << endl;
	if(s != "onetwothree") cout << "PROBLEM!" << endl;

	return 0;
}

