// 9.11 Given a boolean expression consisting of the symbols 0, 1, &, |, and ^,
// and a desired boolean result value, implement a function to count the number
// of ways of parenthesizing the expression such that it evaluates to result.

// The algorithm is following:
//  1. Iterate via given expression
//  2. when the current symbol is an operation, split the expression on left and
//  right parts
//  3. Goto Step 1. with left and right parts separately
//  4 Get the lists of expression parenthesizing ways for the left part and
//  the right part
//  5. Merge that two lists in one resulting list, representing different ways
//  of parenthesizing current expression; calculate the results of expressions
//  ass well
//  6. When all possible ways are calculated, iterate via the list and select
//  expressions, resulting in desired value

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stdlib.h>
#include <time.h>
using namespace std;

class way {
	public:
		string exp;
		bool res;
	public:
		way() : res(false) {}
		way(const string e, bool r) : exp(e), res(r) {}
};

map<string, vector<way> > _m;

bool __use_DP = true;

bool get_val(char c) {
	switch(c) {
		case '0': return false;
		case '1': return true;
		default:
				  cout << "ERROR! Invalid boolean value" << endl;
				  return false;
	}
}

bool do_op(char op, bool v1, bool v2) {
	switch(op) {
		case '&': return (v1 && v2);
		case '|': return (v1 || v2);
		case '^': return (v1 ^ v2);
		default:
				  cout << "ERROR! Invalid boolean operation" << endl;
				  return false;
	}
}

bool is_op(char op) {
	switch(op) {
		case '&':
		case '|':
		case '^':
			return true;
		default:
			return false;
	}
}


void split_expression(const string &exp, vector<way> &ways) {
	//cout << "Processing: " << exp << endl;
	if(__use_DP) {
		if(_m.count(exp) > 0) {
			ways = _m[exp];
			return;
		}
	}

	if(exp.length() == 1) {
		ways.push_back(way(exp, get_val(exp[0])));
		if(__use_DP)
			_m[exp] = ways;
		return;
	}

	if(exp.length() == 3) {
		bool res = do_op(exp[1], get_val(exp[0]), get_val(exp[2]));
		ways.push_back(way(exp, res));
		if(__use_DP)
			_m[exp] = ways;
		return;
	}

	for(size_t i = 0; i < exp.length(); i ++) {
		/* Extract the operation */
		char op = exp[i];
		if(!is_op(op))
			continue;

		/* Process the left part of expression */
		string expl = exp.substr(0, i);
		vector<way> wl;
		split_expression(expl, wl);
		for(size_t l = 0; l < wl.size(); l ++)
			if(wl[l].exp.length() >= 3)
				wl[l].exp = '(' + wl[l].exp + ')';

		/* Process the right part of expression */
		string expr = exp.substr(i + 1);
		vector<way> wr;
		split_expression(expr, wr);
		for(size_t r = 0; r < wr.size(); r ++)
			if(wr[r].exp.length() >= 3)
				wr[r].exp = '(' + wr[r].exp + ')';

		/* Compose processed expression on the base of the left and right
		 * parts */
		for(size_t l = 0; l < wl.size(); l ++) {
			way cur_wl = wl[l];

			for(size_t r = 0; r < wr.size(); r ++) {
				way cur_wr = wr[r];

				way new_way;
				new_way.exp = cur_wl.exp + op + cur_wr.exp;
				new_way.res = do_op(op, cur_wl.res, cur_wr.res);
				ways.push_back(new_way);
			}
		}
	}
	if(__use_DP)
		_m[exp] = ways;
}

int count_ways(const string &expression, bool desired_result, bool verbous = true) {
	if(__use_DP)
		_m.clear();

	cout << "Expression: " << expression << endl;
	cout << "Desired result: " << ((desired_result) ? "true" : "false" ) << endl;
	vector<way> ways;
	split_expression(expression, ways);
	int cnt = 0;
	vector<string> exps;
	for(size_t i = 0; i < ways.size(); i ++) {
		way w = ways[i];
		if(w.res == desired_result) {
			exps.push_back(w.exp);
			cnt ++;
		}
	}

	cout << "Output: " << cnt << " ways." << endl;

	if(verbous) {
		for(size_t i = 0; i < exps.size(); i ++)
			cout << "\t" << exps[i] << endl;
	}

	return cnt;
}

char rnd_bool() {
	if(rand() > (RAND_MAX / 2))
		return true;
	else
		return false;
}

char rnd_val() {
	if(rnd_bool())
		return '1';
	else
		return '0';
}

char rnd_op() {
	if(rand() < (RAND_MAX / 3))
		return '^';
	else if(rand() > ((RAND_MAX / 3) * 2))
		return '&';
	else
		return '|';
}

int main(void) {
	{ /* Test 1 */
		cout << endl << "Test #1" << endl;
		int cnt = count_ways("1^0|0|1", false);
		if(cnt != 2)
			cout << "Error!" << endl;
		else
			cout << "OK" << endl;
		cout << "------------------------------" << endl;
	}

	{ /* Test 1 */
		cout << endl << "Test #2" << endl;
		int cnt = count_ways("1^0|0|1", true);
		if(cnt != 3)
			cout << "Error!" << endl;
		else
			cout << "OK" << endl;
		cout << "------------------------------" << endl;
	}

	{ /* Test 3 */
		cout << endl << "Test #3" << endl;
		int cnt = count_ways("1|0|1|0|1&1&0|0&0^0^1", true, false);
		if(cnt != 12057)
			cout << "Error!" << endl;
		else
			cout << "OK" << endl;
		cnt = count_ways("1|0|1|0|1&1&0|0&0^0^1", false, false);
		if(cnt != 4739)
			cout << "Error!" << endl;
		else
			cout << "OK" << endl;
		cout << "------------------------------" << endl;
	}



	{ /* Serial test */
		cout << endl << "Serial Test" << endl;
		srand(time(NULL));
		string exp;
		exp += rnd_val();
		for(int i = 0; i < 4; i ++) {
			exp += rnd_op();
			exp += rnd_val();
		}
		//count_ways(exp, rnd_bool());
		count_ways(exp, true);
		count_ways(exp, false);
	}

	{ /* Super Serial test */
		cout << endl << "Serial Test" << endl;
		srand(time(NULL));
		string exp;
		exp += rnd_val();
		for(int i = 0; i < 12; i ++) {
			exp += rnd_op();
			exp += rnd_val();
		}
		count_ways(exp, true, false);
		count_ways(exp, false, false);
	}
	return 0;
}
