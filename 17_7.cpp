// 17.7 Given any integer, print an English phrase that describes the integer
// (e.g., "One Thousand, Two Hundred Thirty Four").
#include <iostream>
#include <string>
using namespace std;

const char *ones[] = {"", "one", "two", "three", "four", "five", "six", "seven",
	"eight", "nine"};

const char *teens[] = {"ten", "eleven", "twelver", "thirteen", "fourteen",
	"fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};

const char *decs[] = {"", "ten", "twenty", "thirty", "fourty", "fifty",
	"sixty", "seventy", "eighty", "ninety"};

const char *triads[] = {"", "thousand", "million", "billion"};

string stringify_triad(int a) {
	string s;

	if(a == 0)
		return s;

	int b = a % 100;
	if((1 <= b) && (b <= 9))
		s = ones[b];
	else if((10 <= b) && (b <= 19))
		s = teens[b - 10];
	else if(b >= 20)
		s = string("") + decs[b / 10] + " " + ones[b % 10];

	if(a >= 100)
		s = string("") + ones[a / 100] + " hundreed " + s;

	return s;
}

string stringify(int a) {

	const bool negative = a < 0;
	if(negative)
		a *= -1;

	string s;
	int t = 0;
	while(a) {
		string cur = stringify_triad(a % 1000);
		if(!cur.empty())
			s = cur + " " + triads[t] + ((t && !s.empty()) ? ", " : "") + s;
		t ++;
		a /= 1000;
	}

	if(negative)
		s = "Minus " + s;

	s.erase(s.find_last_not_of(" \n\r\t")+1);

	return s;
}

int main(void) {
	{ //1
		cout << stringify(1234) << endl;
	}

	{ //2
		cout << stringify(102) << endl;
	}

	{ //3
		cout << stringify(1000) << endl;
	}

	{ //4
		cout << stringify(1234567) << endl;
	}

	return 0;

	for(int i = 0; i < 1234; i ++)
		cout << stringify(i) << endl;


	return 0;
}
