#include <iostream>
#include <string>
#include <vector>
using namespace std;

int bs(const vector<string> &a, const string &str, int left, int right) {
	if((left < 0) || (right >= int(a.size())) || (left > right))
		return -1;

	int mid = (left + right) / 2;
	if(a[mid] == str)
		return mid;

	if(a[mid] != " ") {
		if(str < a[mid])
			return bs(a, str, left, mid - 1);
		else
			return bs(a, str, mid + 1, right);
	} else {
		string nextl;
		int ml = mid;
		while(ml >= left) {
			if(a[ml] != " ") {
				nextl = a[ml];
				break;
			}
			ml --;
		}
		if(nextl == str)
			return ml;

		string nextr;
		int mr = mid;
		while(mr <= right) {
			if(a[mr] != " ") {
				nextr = a[mr];
				break;
			}
			mr ++;
		}

		if(nextr == str)
			return mr;

		if(!nextl.empty() && (str < nextl))
			return bs(a, str, left, ml - 1);
		if(!nextr.empty() && (str > nextr))
			return bs(a, str, mr + 1, right);
	}
	return -1;
}

int main(void) {
	vector<string> a;
	a.push_back("at");
	a.push_back(" ");
	a.push_back(" ");
	a.push_back(" ");
	a.push_back("ball");
	a.push_back(" ");
	a.push_back(" ");
	a.push_back("car");
	a.push_back(" ");
	a.push_back(" ");
	a.push_back("dad");
	a.push_back(" ");
	a.push_back(" ");

	cout << bs(a, "ball", 0, int(a.size() - 1)) << endl;
	return 0;
}
