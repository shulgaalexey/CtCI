// Triple Step: A child is running up a staircase with n steps and can hop either 1 step, 2 steps, or 3
// steps at a time. Implement a method to count how many possible ways the child can run up the
// stairs.
import java.util.*;

public class Task_8_1 {
	static Map<Integer, Integer> memo;

	static int doCountWays(final int n) {
		if (n < 0 ) {
			return 0;
		} else if (n == 0) {
			return 1;
		} else {
			if (memo.containsKey(n)) {
				return memo.get(n);
			}

			int res = countWays(n - 1) + countWays(n - 2) + countWays(n - 3);
			memo.put(n, res);
			return res;
		}
	}

	static int countWays(final int n) {
		memo = new HashMap<>();
		return doCountWays(n);
	}

	public static void main(String args[]) {
		for (int i = 0; i < 9; i++) {
			System.out.println(countWays(i));
		}
	}
}
