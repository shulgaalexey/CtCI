#include <iostream>
#include <vector>
using namespace std;

const int N = 5;
int B[N] = {0};
int W[N] = {4, 1,  9, 7, 2};
int H[N] = {4, 1, 10, 6, 3};
int D[N] = {5, 1, 11, 8, 2};

vector<int> global_result;
int global_max = 0;
vector<int> result;

void build(const int h) {

	int prev_w = 1000;
	int prev_h = 1000;
	int prev_d = 1000;
	if(!result.empty()) {
		int index = result[result.size() - 1];
		prev_w = W[index];
		prev_h = H[index];
		prev_d = D[index];
	}

	for(int i = 0; i < N; i ++) {
		if(B[i])
			continue;
		if((W[i] < prev_w) && (H[i] < prev_h) && (D[i] < prev_d)) {
			B[i] = 1;
			result.push_back(i);

			int new_h = h + H[i];

			if(new_h > global_max) {
				global_max = new_h;
				global_result = result;
			}

			build(new_h);

			if(!result.empty())
				result.erase(result.begin() + result.size() - 1);
			B[i] = 0;
		}
	}
}

int main(void) {

	build(0);

	for(size_t i = 0; i < global_result.size(); i ++)
		cout << global_result[i] << " ";
	cout << endl;

	return 0;
}

