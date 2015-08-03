// 9.9 Write an algorithm to print all ways of arranging eight queens on an 8x8
// chess board so that none of them share the same row, collumn or diagonal. In
// this case, "diagonal" means all diagonals, not just the two bisect the
// board.


// Solution Idea:
//  The Board is a set of columns, rows and diagonals with following indexation of cells:
//    0 1 2 3 4 5 6 7
//  0                0
//  1                1
//  2                2
//  3                3
//  4                4
//  5                5
//  6                6
//  7                7
//    0 1 2 3 4 5 6 7
//
//  Process four arrays:
//   * Vertical cell lines (collumns), totally 8 lines
//   * Horizontal cell lines (rows), totally 8 lines
//   * Positive diagonals, such ad (0, 0) to (7, 7), totally 14 lines
//   * Negative diagonals, such as (7, 0) to (0, 7), totally 14 lines
//
//  Algorithm steps:
//  Iterate via horizontal lines (because each queen must stand on its own row).
//  Test each available cell on the current row and put a queen there if it is free.
//  Mark those row, collumn and diagonals as occupied (set to "true")
//  Then go to next row and repeat those steps.
//  On the final row print the array of queens.
//
//  To check if the cell is available, check the array of columns and diagonals:
//   the cell has value "true" if occupied.
//
//  Note:
//   * the index of horizontal line in the array is y
//   * the index of horizontal line in the array is x
//	 * the index of positive diagonal in the array is (7 + x - y),
//   * the index of the negative diagonal is (x + y).

#include <iostream>
using namespace std;

class queen {
	public:
		int x;
		int y;
	public:
		queen() : x(-1), y(-1) {}
		queen(int X, int Y) : x(X), y(Y) {}
};

queen _q[8]; // Set of queens

bool lvert[8] = { 0 }; // Vertical cell lines (collumns)
bool lhorz[8] = { 0 }; // Horizontal cell lines (rows)
bool dpos[14] = { 0 }; // Positive diagonals Ex. (0, 0) to (7, 7)
bool dneg[14] = { 0 }; // Negative diagonals Ex. (7, 0) to (0, 7)

void perform_print_queen_board(int y);
void queens_on_screen();

void print_queen_board() {
	for(int i = 0; i < 8; i ++)
		_q[i] = queen();

	perform_print_queen_board(0);
}

void perform_print_queen_board(int y) {
	lhorz[y] = true;
	for(int x = 0; x < 8; x ++) {
		if(!lvert[x] && !dpos[7 + x - y] && !dneg[x + y]) {
			_q[y] = queen(x,y);
			if(y == 7)
				queens_on_screen();
			else {
				lvert[x] = true;
				dpos[7 + x - y] = true;
				dneg[x + y] = true;
				perform_print_queen_board(y + 1);
				lvert[x] = false;
				dpos[7 + x - y] = false;
				dneg[x + y] = false;
			}
			_q[y] = queen();
		}
	}
}

void queens_on_screen() {
	for(int y = 0; y < 8; y ++) {
		for(int x = 0; x < _q[y].x; x ++)
			cout << "0";
		cout << "X";
		for(int x = (_q[y].x + 1); x < 8; x ++)
			cout << "0";
		cout << endl;
	}
	cout << endl;
}

int main(void) {
	print_queen_board();
	return 0;
}
