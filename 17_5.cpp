// 17.5
#include <iostream>
using namespace std;


// Idea: use prime numbers to encode colors, so the single compressed solution
// would be a multiplication of all color codes.
// It will allow to estimate pseudo-hits easily by using devision, because
// the compressed value would store color frequencies.
int compress_color(const char c) {
	switch(c) {
		case 'R': return 3;
		case 'G': return 5;
		case 'B': return 7;
		case 'Y': return 11;
	}
	return 0;
}

void count_hits(const char guess[4], const char solution[4],
		int *hits, int *pseudo_hits) {
	*hits = 0;

	// 1. Count hits
	for(int i = 0; i < 4; i ++)
		if((guess[i] - solution[i]) == 0)
			(*hits) ++;

	// 2. Count pseoud-hits
	*pseudo_hits = 0;
	int S = 1; // Compressed solution: R:3, G:5, B:7, Y:11
	for(int i = 0; i < 4; i ++)
		S *= compress_color(solution[i]);


	for(int i = 0; i < 4; i ++) {
		const char G = compress_color(guess[i]);
		if((S % G) == 0) {
			(*pseudo_hits) ++;
			S /= G;
		}
	}

	(*pseudo_hits) -= (*hits);
}

///////////////////////////////////////////////////////////////////////////////
#define min(a,b) ((a<b)?a:b)
void count_hits2(const char guess[4], const char solution[4],
		int *hits, int *pseudo_hits) {
	*hits = 0;
	*pseudo_hits = 0;

	int R_g_cnt = 0;
	int G_g_cnt = 0;
	int B_g_cnt = 0;
	int Y_g_cnt = 0;
	int R_s_cnt = 0;
	int G_s_cnt = 0;
	int B_s_cnt = 0;
	int Y_s_cnt = 0;

	// 1. Count hits
	for(int i = 0; i < 4; i ++) {
		if((guess[i] - solution[i]) == 0)
			(*hits) ++;

		switch(guess[i]) {
			case 'R': R_g_cnt ++; break;
			case 'G': G_g_cnt ++; break;
			case 'B': B_g_cnt ++; break;
			case 'Y': Y_g_cnt ++; break;
		}

		switch(solution[i]) {
			case 'R': R_s_cnt ++; break;
			case 'G': G_s_cnt ++; break;
			case 'B': B_s_cnt ++; break;
			case 'Y': Y_s_cnt ++; break;
		}
	}


	if(R_g_cnt && R_s_cnt)
		(*pseudo_hits) += min(R_g_cnt, R_s_cnt);

	if(G_g_cnt && G_s_cnt)
		(*pseudo_hits) += min(G_g_cnt, G_s_cnt);

	if(B_g_cnt && B_s_cnt)
		(*pseudo_hits) += min(B_g_cnt, B_s_cnt);

	if(Y_g_cnt && Y_s_cnt)
		(*pseudo_hits) += min(Y_g_cnt, Y_s_cnt);

	(*pseudo_hits) -= (*hits);
}

int main(void) {
	{ // 1
		const char guess[4] = {'G', 'G', 'R', 'R'};
		const char solution[4] = {'R', 'G', 'B', 'Y'};
		int hits = 0;
		int pseudo_hits = 0;
		count_hits(guess, solution, &hits, &pseudo_hits);
		if((hits != 1) || (pseudo_hits != 1))
				cout << "ERROR1" << endl;
		count_hits2(guess, solution, &hits, &pseudo_hits);
		if((hits != 1) || (pseudo_hits != 1))
				cout << "ERROR1_2" << endl;
	}

	{ // 2
		const char guess[4] = {'Y', 'R', 'G', 'B'};
		const char solution[4] = {'R', 'G', 'G', 'B'};
		int hits = 0;
		int pseudo_hits = 0;
		count_hits(guess, solution, &hits, &pseudo_hits);
		if((hits != 2) || (pseudo_hits != 1))
				cout << "ERROR2" << endl;
		count_hits2(guess, solution, &hits, &pseudo_hits);
		if((hits != 2) || (pseudo_hits != 1))
				cout << "ERROR2_2" << endl;
	}
	return 0;
}
