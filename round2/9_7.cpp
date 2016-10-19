#include <iostream>
#include <queue>
using namespace std;

const int M = 12;
const int N = 10;
int G[M][N] = {0};

void fill(int x, int y, int color) {
	int orig_color = G[y][x];
	queue<pair<int, int> > q;
	q.push(pair<int, int>(x, y)); // x:j   y:i
	while(!q.empty()) {
		pair<int, int> cur = q.front();
		q.pop();
		int i = cur.second;
		int j = cur.first;
		G[i][j] = color;
		if(((i + 1) < M) && (G[i + 1][j] == orig_color))
			q.push(pair<int, int>(j, i + 1));
		if(((i - 1) >= 0) && (G[i - 1][j] == orig_color))
			q.push(pair<int, int>(j, i - 1));
		if(((j + 1) < N) && (G[i][j + 1] == orig_color))
			q.push(pair<int, int>(j + 1, i));
		if(((j - 1) >= 0) && (G[i][j - 1] == orig_color))
			q.push(pair<int, int>(j - 1, i));
	}
}

void print() {
	for(int i = 0; i < M; i ++) {
		for(int j = 0; j < N; j ++) {
			cout << G[i][j] << " ";
		}
		cout << endl;
	}
}

int main(void) {

	G[2][3] = 1;
	G[2][4] = 1;
	G[2][5] = 1;
	G[3][6] = 1;
	G[4][6] = 1;
	G[5][7] = 1;
	G[6][7] = 1;
	G[7][6] = 1;
	G[7][5] = 1;
	G[7][4] = 1;
	G[7][3] = 1;
	G[6][3] = 1;
	G[5][3] = 1;
	G[4][2] = 1;
	G[3][2] = 1;

	print();

	cout << "-------------------" << endl;

	fill(4, 4, 8);
	print();

	cout << "-------------------" << endl;

	fill(0, 0, 3);
	print();

	return 0;
}
