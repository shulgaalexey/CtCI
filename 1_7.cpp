// 1.7 Write an algorithm such that if an element in an MxN matrix is 0,
// its entire row and column are set to 0;

#include <iostream>
#include <map>

using namespace std;

void trace(int *m, const int M, const int N) {
	for(int i = 0; i < M; i ++) {
		for(int j = 0; j < N; j ++) {
			cout << m[i*N+j] << " ";
		}
		cout << endl;
	}
}

void modify(int *m, const int M, const int N) {
	map<int, int> mi;
	map<int, int> mj;

	for(int i = 0; i < M; i ++) {
		for(int j = 0; j < N; j ++) {
			if(!m[i*N+j]) {
				mi[i] = 1;
				mj[j] = 1;
			}
		}
	}

	for(int i = 0; i < M; i ++) {
		for(int j = 0; j < N; j ++) {
			if(mi.count(i) || mj.count(j))
				m[i*N+j] = 0;
		}
	}
}

bool equal(int *m, int *t, const int M, const int N) {
	for(int i = 0; i < M; i ++)
		for(int j = 0; j < N; j ++)
			if(m[i*N+j] != t[i*N+j])
				return false;
	return true;
}

int main() {
	{ // test 1
		const int M = 6;
		const int N = 5;
		int m[M][N] = {
				{1, 2, 3, 4, 5},
				{6, 7, 8, 0, 9},
				{10, 11, 12, 13, 14},
				{15, 0, 16, 17, 18},
				{19, 20, 21, 22, 23},
				{24, 25, 26, 27, 28}};
		trace((int *)m, M, N);
		modify((int *)m, M, N);
		trace((int *)m, M, N);
		int t[M][N] = {
				{1, 0, 3, 0, 5},
				{0, 0, 0, 0, 0},
				{10, 0, 12, 0, 14},
				{0, 0, 0, 0, 0},
				{19, 0, 21, 0, 23},
				{24, 0, 26, 0, 28}};
		if(!equal((int *)m, (int *)t, M, N)) cout << "PROBLEM!" << endl;
	}

	return 0;
}
