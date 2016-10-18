#include <iostream>
#include <vector> // for path
using namespace std;

const int M = 5;
const int N = 6;
int G[M][N] = {0};
int Obst[M][N] = {0};

int cnt_path(int i, int j) {
	if((i == (M - 1)) && (j == (N - 1)))
		return 1;
	else if((i >= M) || (j >= N))
		return 0;
	else if(G[i][j])
		return G[i][j];
	else {
		G[i][j] = 1 + cnt_path(i + 1, j) + cnt_path(i, j + 1);
		return G[i][j];
	}
}

bool found = false;
vector<pair<int, int> > path;
void gen_path(int i, int j) {
	if(found)
		return;
	if((i == (M - 1)) && (j == (N - 1))) {
		found = true;
		path.push_back(pair<int, int>(i, j));
		for(size_t i = 0; i < path.size(); i ++)
			cout << path[i].first << "," << path[i].second << endl;
		return;
	} else if((i >= M) || (j >= N))
		return;
	else if(Obst[i][j])
		return;
	else {
		path.push_back(pair<int, int>(i, j));
		gen_path(i + 1, j);
		gen_path(i, j + 1);
		path.erase(path.end());
	}
}

int main(void) {
	Obst[1][1] = 1;
	Obst[1][2] = 1;
	Obst[2][4] = 1;
	Obst[3][4] = 1;
	Obst[3][0] = 1;
	Obst[3][1] = 1;

	cout << cnt_path(0, 0) << endl;
	gen_path(0, 0);
	return 0;
}
