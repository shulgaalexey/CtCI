// Coins: Given an infinite number of quarters (25 cents), dimes (10 cents), nickels (5 cents), and
// pennies (1 cent), write code to calculate the number of ways of representing n cents.
import java.util.*;

public class Task_8_11 {

	static int calcWays(final int n) {
		int sum = 0;
		int cnt = 0;
		for (int i = 0; i <= (n / 25); i++) {
			int cur = n - i * 25;
			if (cur < 0) {
				break;
			}
			for (int j = 0; j <= ((n - i * 25) / 10); j++) {
				cur = n - i * 25 - j * 10;
				if (cur < 0) {
					break;
				}

				for (int k = 0; k <= ((n - i * 25 - j * 10) / 5); k++) {
					cur = n - i * 25 - j * 10 - k * 5;
					if (cur < 0) {
						break;
					}

					cnt++;
					if (cur >= 0 || cur < 5) {
						sum++;
						System.out.println(String.format("%d, %d, %d, %d", i, j, k, cur));
					}
				}
			}
		}
		return sum;
	}

	static int makeChange(final int n) {
		int[] denoms = {25, 10, 5, 1};
		int[][] map = new int[n + 1][denoms.length];
		return makeChange(n, denoms, 0, map);
	}

	static int makeChange(final int amount, int[] denoms, int index, int[][] map) {
		if (map[amount][index] > 0) {
			return map[amount][index];
		}
		if (index >= (denoms.length - 1)) {
			return 1;
		}
		int denomAmount = denoms[index];
		int ways = 0;
		for (int i = 0; (i * denomAmount) <= amount; i++) {
			int amountRemaining = amount - i * denomAmount;
			ways += makeChange(amountRemaining, denoms, index + 1, map);
		}
		map[amount][index] = ways;
		return ways;
	}

	public static void main(String args[]) {
		System.out.println("Calc ways for 90: " + calcWays(98));
		System.out.println("Calc ways for 90: " + makeChange(98));
	}
}
