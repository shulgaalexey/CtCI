// Design an algorithm to figure out if someone has wom a game of tic-tac-toe.
#include <iostream>
using namespace std;

static unsigned int x_won[8] = {0};
static unsigned int o_won[8] = {0};
static const char X = 'X';
static const char O = 'O';
static const char E = 'E';

void generate_won_boards();

unsigned int compress_board(const char *board, const char c) { // assumed 3x3 board
	// Convert the whole board into one integer.
	// Use pair of bits for each value of the cell:
	//     'X' -> 01, 'O' -> 10, '_' -> 00
	unsigned char mask = (c == X) ? 1 : ((c == O) ? 2 : 0);
	unsigned int b = 0;
	for(int i = 0; i < 9; i ++)
		if(board[i] == c)
			b |= mask << (i << 1);
	return b;
}

char is_won(const char *board) { // assumed 3x3 board

	// 1. Check if current board is a won by X
	{
		const unsigned int cur_bx = compress_board(board, X);
		for(int i = 0; i < 16; i ++)
			if(cur_bx == x_won[i])
				return X;
	}

	// 2. Check if current board is a won by O
	{
		const unsigned int cur_bo = compress_board(board, O);
		for(int i = 0; i < 16; i ++)
			if(cur_bo == o_won[i])
				return O;
	}

	// 3. No win solution is found, so the game is not won
	return E;
}

int main(void) {
	// Pre-computing
	generate_won_boards();

	// Test cases

	{ // 1
		const char board[] = {
			E, E, E,
			X, X, X,
			E, E, E
		};
		if(is_won(board) != X)
			cout << "ERROR1" << endl;

	}

	{ // 2
		const char board[] = {
			O, X, O,
			O, X, X,
			X, O, X
		};
		if(is_won(board) != E)
			cout << "ERROR2" << endl;

	}

	{ // 3
		const char board[] = {
			E, X, O,
			X, O, E,
			O, E, X
		};
		if(is_won(board) != O)
			cout << "ERROR3" << endl;

	}

	return 0;
}

void generate_won_boards() {
	int i = 0;

	// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

	{ // X wins by row
		const char XA1[] = {
			X, X, X,
			E, E, E,
			E, E, E
		};
		x_won[i++] = compress_board(XA1, X);

		const char XA2[] = {
			E, E, E,
			X, X, X,
			E, E, E
		};
		x_won[i++] = compress_board(XA2, X);

		const char XA3[] = {
			E, E, E,
			E, E, E,
			X, X, X,
		};
		x_won[i++] = compress_board(XA3, X);
	}

	{ // X wins by collumn
		const char XB1[] = {
			X, E, E,
			X, E, E,
			X, E, E
		};
		x_won[i++] = compress_board(XB1, X);

		const char XB2[] = {
			E, X, E,
			E, X, E,
			E, X, E
		};
		x_won[i++] = compress_board(XB2, X);

		const char XB3[] = {
			E, E, X,
			E, E, X,
			E, E, X
		};
		x_won[i++] = compress_board(XB3, X);
	}

	{ // X wins by diagonal
		const char XC1[] = {
			X, E, E,
			E, X, E,
			E, E, X
		};
		x_won[i++] = compress_board(XC1, X);

		const char XC2[] = {
			E, E, X,
			E, X, E,
			X, E, E
		};
		x_won[i++] = compress_board(XC2, X);
	}

	// OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO

	i = 0;
	{ // O wins by row
		const char OA1[] = {
			O, O, O,
			E, E, E,
			E, E, E
		};
		o_won[i++] = compress_board(OA1, O);

		const char OA2[] = {
			E, E, E,
			O, O, O,
			E, E, E
		};
		o_won[i++] = compress_board(OA2, O);

		const char OA3[] = {
			E, E, E,
			E, E, E,
			O, O, O,
		};
		o_won[i++] = compress_board(OA3, O);
	}

	{ // O wins by collumn
		const char OB1[] = {
			O, E, E,
			O, E, E,
			O, E, E
		};
		o_won[i++] = compress_board(OB1, O);

		const char OB2[] = {
			E, O, E,
			E, O, E,
			E, O, E
		};
		o_won[i++] = compress_board(OB2, O);

		const char OB3[] = {
			E, E, O,
			E, E, O,
			E, E, O
		};
		o_won[i++] = compress_board(OB3, O);
	}

	{ // O wins by diagonal
		const char OC1[] = {
			O, E, E,
			E, O, E,
			E, E, O
		};
		o_won[i++] = compress_board(OC1, O);

		const char OC2[] = {
			E, E, O,
			E, O, E,
			O, E, E
		};
		o_won[i++] = compress_board(OC2, O);
	}
}
