// 11.2 Write a method to sort an array of strings so that all the anagrams are
// next to each other
#include <iostream>
#include <string>
#include <vector>
#include <string.h>
using namespace std;

void count_sort(string &s) {
	int cnts[26] = {0};
	for(size_t i = 0; i < s.length(); i ++)
		cnts[s[i] - 'a'] ++;
	int idx = 0;
	for(int i = 0; i < 26; i ++)
		for(int j = 0; j < cnts[i]; j ++)
			s[idx++] = char('a' + i);
}

class word {
public:
	string orig;
	string srt;
public:
	word(){};
	word(const string &o) : orig(o), srt(o) {
		count_sort(srt);
	}
	bool operator>(const word &w) const {
		return (strcmp(srt.c_str(), w.srt.c_str()) > 0);
	}
};

void merge(vector<word> &W, const vector<word> &l, const vector<word> &r) {
	size_t l_idx = 0;
	size_t r_idx = 0;
	size_t ins_idx = 0;
	size_t total = l.size() + r.size();
	vector<word> res(total);
	W = res;
	while(true) {
		if(l_idx >= l.size())
			break;
		if(r_idx >= r.size())
			break;
		if(l[l_idx] > r[r_idx])
			W[ins_idx ++] = r[r_idx ++];
		else
			W[ins_idx ++] = l[l_idx ++];
	}

	while(l_idx < l.size())
		W[ins_idx ++] = l[l_idx ++];
	while(r_idx < r.size())
		W[ins_idx ++] = r[r_idx ++];
}

vector<word> merge_sort_r(vector<word> &W, int left, int right) {
	vector<word> ret;
	int len = right - left;

	if(len < 0)
		return ret;
	if(len == 0) {
		ret.push_back(W[left]);
		return ret;
	}
	if(len == 1) {
		if(W[left] > W[right]) {
			ret.push_back(W[right]);
			ret.push_back(W[left]);
		} else {
			ret.push_back(W[left]);
			ret.push_back(W[right]);
		}
		return ret;
	}

	const int mid = (left + right) / 2;
	vector<word> l = merge_sort_r(W, left, mid - 1);
	vector<word> r = merge_sort_r(W, mid, right);
	merge(ret, l, r);
	return ret;
}

void merge_sort(vector<word> &W) {
	const int right = int(W.size()) - 1;
	int mid = right / 2;
	vector<word> l = merge_sort_r(W, 0, mid - 1);
	vector<word> r = merge_sort_r(W, mid, right);
	merge(W, l, r);
}

vector<string> solution(const vector<string> &A) {
	const int N = int(A.size());
	vector<word> W(N);
	for(int i = 0; i < N; i ++)
		W[i] = word(A[i]);

	merge_sort(W);

	vector<string> res(N);
	for(int i = 0; i < N; i ++)
		res[i] = W[i].orig;

	return res;
}

int main(void) {
	{ // 1
		vector<string> A;
		A.push_back("cab");
		A.push_back("aab");
		A.push_back("abc");
		A.push_back("aba");
		A.push_back("def");
		A.push_back("baa");
		A.push_back("klm");
		A.push_back("ijk");

		vector<string> res = solution(A);
		for(size_t i = 0; i < res.size(); i ++)
			cout << res[i] << endl;
	}

	return 0;
}
