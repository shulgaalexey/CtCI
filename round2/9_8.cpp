#include <iostream>
using namespace std;

int denoms[] = {25, 10, 5, 1};
const int DENOM_CNT = 4;
const int AMOUNT = 117;
int DP[AMOUNT][DENOM_CNT] = {0};


int make_change(int amount, int index) {
	if(DP[amount][index])
		return DP[amount][index];

	if(index >= (DENOM_CNT - 1))
		return 1;

	int denom_amount = denoms[index];
	int ways = 0;
	for(int i = 0; i * denom_amount <= amount; i ++) {
		int amount_remaining = amount - i * denom_amount;
		ways += make_change(amount_remaining, index + 1);
	}
	DP[amount][index] = ways;
	return ways;
}

int main(void) {
	cout << make_change(AMOUNT, 0) << endl;
	return 0;
}
