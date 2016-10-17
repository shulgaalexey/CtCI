#include <iostream>
using namespace std;

int count_ways(const int n, int *dp) {
	if(n < 0)
		return 0;
	else if(n == 0)
		return 1;
	else if(dp[n] > (-1))
		return dp[n];
	else {
		dp[n] = count_ways(n - 1, dp)
			+ count_ways(n - 2, dp)
			+ count_ways(n - 3, dp);
		return dp[n];
	}
}

int main(void) {
	for(int i = 1; i < 10; i ++) {
		const int n = i;
		int dp[n + 1] = {0};
		for(int j = 0; j < (n + 1); j ++)
			dp[j] = -1;
		cout << count_ways(n, dp) << endl;
	}
	return 0;
}
