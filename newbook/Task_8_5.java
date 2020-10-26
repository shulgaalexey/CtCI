// Recursive Multiply: Write a recursive function to multiply two positive integers without using the
// *operator.You can use addition, subtraction, and bit shifting, but you should minimize the number
// of those operations.
import java.util.*;

public class Task_8_5 {
	static boolean even(final Integer a) {
		return ((a >> 1) << 1) == a;
	}

	static Integer doMul(final Integer a, final Integer b, Map<Integer, Integer> memo) {
		if (a == 0 || b == 0) {
			return 0;
		}
		if (a == 1) {
			return b;
		}
		if (b == 1) {
			return a;
		}

		/*if (memo.containsKey(a)) {
			return memo.get(a);
		}*/

		final Integer halfa = a >> 1;
		Integer tmp = doMul(halfa, b, memo);
		tmp += tmp;
		if (!even(a)) {
			tmp += b;
		}
		//memo.put(a, tmp);
		return tmp;
	}

	static Integer mul(final Integer a, final Integer b) {
		//Map<Integer, Integer> memo = new HashMap<>();
		if (a > b) {
			return doMul(a, b, null);
		} else {
			return doMul(b, a, null);
		}
	}

	public static void main(String args[]) {
		System.out.println(mul(13, 49) == 637);


		long startTime = System.currentTimeMillis();
		for (Integer i = 0; i < 10000; i++) {
			for (Integer j = 0; j < 10000; j++) {
				if (mul(i, j) != (i * j)) {
					System.out.println("ERROR for " + i + ", " + j);
				}
			}
		}
		long estimatedTime = System.currentTimeMillis() - startTime;
		System.out.println("Time: " + estimatedTime);
	}
}
