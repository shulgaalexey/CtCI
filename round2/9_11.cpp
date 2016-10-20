#include <iostream>
using namespace std;

const int N = 7;
int args[N] = {1, 4, 0, 3, 0, 3, 1};
bool expected = false;
int cnt = 0;

int DP[N][N] = {0};

bool do_op(const int op, const int arg1, const int arg2) {
	switch(op) {
		case 2:
			return bool(arg1) & bool(arg2);
		case 3:
			return bool(arg1) | bool(arg2);
		case 4:
			return bool(arg1) ^ bool(arg2);
	}
	cout << "ERROR" << endl;
	return true;
}

// return
// 0 - only false
// 1 - only true
// 2 - both possible
int eval(int left, int right) {
	if(DP[left][right] >= 0)
		return DP[left][right];

	if(right == left)
		return args[left];
	else if((right - left) == 2) {
		DP[left][right] = do_op(args[left + 1], args[left], args[right]);
		return DP[left][right];
	} else {
		int out[2] = {0};
		int i = left;
		while(i < (right - 1)) {
			int op = args[i + 1];
			if(i == (right - 2)) {
				int r1 = eval(left, i);
				bool res = false;
				switch(r1) {
					case 0:
						res = do_op(op, false, args[right]);
						out[res] = 1;
						break;
					case 1:
						res = do_op(op, true, args[right]);
						out[res] = 1;
						break;
					case 2:
						res = do_op(op, true, args[right]);
						out[res] = 1;
						res = do_op(op, false, args[right]);
						out[res] = 1;
						break;
				}
			} else {
				int r1 = eval(left, i);
				int r2 = eval(i + 2, right);
				bool res = false;
				if((r1 != 2) && (r2 != 2)) {
					res = do_op(op, r1, r2);
					out[res] = 1;
				} else {
					res = do_op(op, true, false);
					out[res] = 1;
					res = do_op(op, false, false);
					out[res] = 1;
					res = do_op(op, true, true);
					out[res] = 1;
				}

			}
			if((left == 0) && (right == (N - 1)) && out[expected])
				cnt ++;

			/*{
				cout << "[" << left << ", " << right << "]: ";
				if(out[0])
					cout << "false ";
				if(out[1])
					cout << "true";
				cout << endl;
			} */

			i += 2;


		}

		/*{
			cout << "[" << left << ", " << right << "]: ";
			if(out[0])
				cout << "false ";
			if(out[1])
				cout << "true";
			cout << endl;
		} */

		if(out[0] && out[1])
			DP[left][right] = 2;
		if(out[0])
			DP[left][right] = 0;
		else
			DP[left][right] = 1;
		return DP[left][right];
	}
}

int main(void) {
	for(int i = 0; i < N; i ++)
		for(int j = 0; j < N; j ++)
			DP[i][j] = -1;

	eval(0, N - 1);

	cout << cnt << endl;

	return 0;
}
