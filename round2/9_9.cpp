#include <iostream>
using namespace std;

int B[8][8] = {0};

void print() {
	cout << "================" << endl;
	for(int i = 0; i < 8; i ++) {
		for(int j = 0; j < 8; j ++) {
			if(B[i][j] > 0)
				cout << "@ ";
			else
				cout << "- ";
		}
		cout << endl;
	}
}

bool check_board(const int i, const int j) {

	for(int x = j, y = i; ((x < 8) && (y < 8)); x ++, y ++) {
		if(B[y][x])
			return false;
	}
	for(int x = j, y = i; ((x >= 0) && (y < 8)); x --, y ++) {
		if(B[y][x])
			return false;
	}

	for(int x = j, y = i; ((x >= 0) && (y >= 0)); x --, y --) {
		if(B[y][x])
			return false;
	}
	for(int x = j, y = i; ((x < 8) && (y >= 0)); x ++, y --) {
		if(B[y][x])
			return false;
	}

	for(int y = 0; y < 8; y ++)
		if(B[y][j])
			return false;

	for(int x = 0; x < 8; x ++)
		if(B[i][x])
			return false;

	return true;
}

void arrange(const int index) {
	if(index > 7)
		return;
	for(int i = 0; i < 8; i ++) {
		if(!check_board(i, index))
			continue;

		B[i][index] = 1;
		arrange(index + 1);

		if(index == 7)
			print();

		B[i][index] = 0;

	}
}

int main(void) {
	arrange(0);
	return 0;
}
