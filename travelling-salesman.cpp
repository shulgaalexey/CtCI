// Traveler Salesman Problem
// Finding the shortest way across all cities
#include <iostream>
#include <climits>

using namespace std;

int row_min(int *a, int N, bool *skip_col, int row) {
	int m = INT_MAX;
	for(int j = 0; j < N; j ++) {
		if(skip_col[j]) continue;
		int idx = row * N + j;
		if(a[idx] == (-1)) continue;
		if(a[idx] < m)
			m = a[idx];
	}
	return m;
}

int col_min(int *a, int N, bool *skip_row, int col) {
	int m = INT_MAX;
	for(int i = 0; i < N; i ++) {
		if(skip_row[i]) continue;
		int idx = i * N + col;
		if(a[idx] == (-1)) continue;
		if(a[idx] < m)
			m = a[idx];
	}
	return m;
}

int row_min_excl(int *a, int N, bool *skip_col, int row, int col) {
	int m = INT_MAX;
	for(int j = 0; j < N; j ++) {
		if(j == col) continue;
		if(skip_col[j]) continue;
		int idx = row * N + j;
		if(a[idx] == (-1)) continue;
		if(a[idx] < m)
			m = a[idx];
	}
	return m;
}

int col_min_excl(int *a, int N, bool *skip_row, int row, int col) {
	int m = INT_MAX;
	for(int i = 0; i < N; i ++) {
		if(i == row) continue;
		if(skip_row[i]) continue;
		int idx = i * N + col;
		if(a[idx] == (-1)) continue;
		if(a[idx] < m)
			m = a[idx];
	}
	return m;
}

void row_sub(int *a, int N, bool *skip_col, int m, int row) {
	for(int j = 0; j < N; j ++) {
		if(skip_col[j]) continue;
		int idx = row * N + j;
		if(a[idx] == (-1)) continue;
		a[idx] -= m;
	}
}

void col_sub(int *a, int N, bool *skip_row, int m, int col) {
	for(int i = 0; i < N; i ++) {
		if(skip_row[i]) continue;
		int idx = i * N + col;
		if(a[idx] == (-1)) continue;
		a[idx] -= m;
	}
}

int tsp(int *a, const int N) {
	int b[N * N];
	for(int i = 0; i < (N * N); i ++)
		b[i] = a[i];

	bool skip_col[N];
	bool skip_row[N];
	for(int i = 0; i < N; i ++) {
		skip_col[i] = false;
		skip_row[i] = false;
	}

	int waypoints[N + 1];
	int pos = 0; // pos of growing way points array

	while(true) {
		// 1. Calc min in each row
		for(int i = 0; i < N; i ++) {
			if(skip_row[i]) continue;
			int m = row_min(a, N, skip_col, i);
			row_sub(a, N, skip_col, m, i);
		}

		// 2. Calc min in each col
		for(int j = 0; j < N; j ++) {
			if(skip_col[j]) continue;
			int m = col_min(a, N, skip_row, j);
			col_sub(a, N, skip_row, m, j);
		}

		// 3. Calc the biggest estimation
		int estim = INT_MIN;
		int ei = -1, ej = -1;
		for(int i = 0; i < N; i ++) {
			if(skip_row[i]) continue;
			for(int j = 0; j < N; j ++) {
				if(skip_col[i]) continue;
				int idx = i * N + j;
				if(a[idx] != 0) continue;
				int e = row_min_excl(a, N, skip_col, i, j)
					+ col_min_excl(a, N, skip_col, i, j);
				if(e > estim) {
					estim = e;
					ei = i;
					ej = j;
				}
			}
		}

		// 4. Register another way segment,
		// remove the col&row, proceede
		waypoints[pos ++] = ei;
		waypoints[pos ++] = ej;

		skip_row[ei] = true;
		skip_col[ej] = true;
		if(pos == N)
			break;
	}

	// Add the return to the starting point
	// (to make the route circular)
	waypoints[pos] = waypoints[0];

	// Trace the route
	cout << "Circular way: ";
	for(int i = 0; i < N; i ++)
		cout << waypoints[i] << " -> ";
	cout << waypoints[N] << endl;

	// Calculate the length of the way
	int way = 0;
	for(int i = 1; i <= N; i ++) {
		int from = waypoints[i - 1];
		int to = waypoints[i];
		way += b[from * N + to];
	}

	return way;
}

int main(void) {
	{ // 1
		const int N = 4;
		int a[] = {
			-1,	5,	11,	9,
			10,	-1,	8,	7,
			7,	14,	-1,	8,
			12,	6,	15,	-1
		};
		int way = tsp(a, N);
		cout << "Length: " << way << endl;
		if(way != 30)
			cout << "ERROR" << endl;
	}

	{ // 2
		const int N = 6;
		int a[] = {
			-1,	6,	4,	8,	7,	14,
			6,	-1,	7,	11,	7,	10,
			4,	7,	-1,	4,	3,	10,
			8,	11,	4,	-1,	5,	11,
			7,	7,	3,	5,	-1,	7,
			14,	10,	10,	11,	7,	-1
		};
		int way = tsp(a, N);
		cout << "Length: " << way << endl;
		if(way != 42)
			cout << "ERROR" << endl;
	}

	return 0;
}
