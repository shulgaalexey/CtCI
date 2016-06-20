// 18.11 Imagine you have a square matrix, where each cell (pixel) is either
// black or white. Design an algorithm to find the maximum subsquare such that
// all four borders are filled with black pixels.
#include <iostream>
using namespace std;

int *a = NULL;
int N = 0;
pair<int, int> *preproc = NULL;

void preprocess() {
	for(int r = (N - 1); r >= 0; r --) {
		for(int c = (N -1); c >= 0; c--) {
			if(a[r * N + c] == 1) { // White pixel
				preproc[r * N + c] = pair<int, int>(0, 0);
				continue;
			}

			// Black pixel: count black pixels to the right and below
			pair<int, int> cur(1, 1);
			if((c + 1) < N)
				cur.first += preproc[r * N + c + 1].first;
			if((r + 1) < N)
				cur.second += preproc[(r + 1) * N + c].second;
			preproc[r * N + c] = cur;
		}
	}
}

bool find_square(int size, pair<int, int> *s) {
	for(int r = 0; r < (N - size + 1); r ++) {
		for(int c = 0; c < (N - size + 1); c ++) {
			pair<int, int> top_left = preproc[r * N + c];
			pair<int, int> top_right = preproc[r * N + c + size - 1];
			pair<int, int> bottom_left = preproc[(r + size - 1) * N + c];
			if((top_left.first >= size) && (top_left.second >= size)
					&& (top_right.second >= size)
					&& (bottom_left.first >= size)) {
				*s = pair<int, int>(r, c);
				return true;
			}
		}
	}
	return false;
}

bool find_max_square(int *size, pair<int, int> *s) {
	preprocess();
	for(int i = N; i > 0; i --) {
		if(find_square(i, s)) {
			*size = i;
			return true;
		}
	}
	*size = 0;
	return false;
}

void set_black(int r, int c) {
	a[r * N + c] = 0;
}

int main(void) {
	{ // 1
		N = 4;
		a = new int[N * N];
		preproc = new pair<int, int>[N * N];

		for(int i = 0; i < (N * N); i ++)
			a[i] = 1; // All white
		set_black(0, 0);
		set_black(1, 1);
		set_black(1, 2);
		set_black(1, 3);
		set_black(2, 1);
		set_black(3, 1);
		set_black(3, 2);
		set_black(3, 3);
		set_black(2, 3);

		pair<int, int> s(-1, -1);
		int size = -1;

		if(!find_max_square(&size, &s))
			cout << "ERROR" << endl;
		else {
			cout << "Size: " << size;
			cout << ", [" << s.first << ", " << s.second << "]" << endl;
		}

		delete [] a;
		delete [] preproc;
	}

	return 0;
}
