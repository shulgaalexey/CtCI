// Design an algorithm to find all pairs of integers within an array which sum
// to a specified value.
import java.util.*;

public class Task_17_12 {

	static void findPairs(Integer a[], Integer S) {
		Map<Integer, Integer> m = new HashMap<>();
		for (int i = 0; i < a.length; i++) {
			m.put(a[i], a[i]);
		}

		for (int i = 0; i < a.length; i++) {
			if (m.containsKey(S - a[i])) {
				System.out.println(a[i] + " + " + (S - a[i]) + " = " + S);
			}
		}
	}

	public static void main(String args[]) {
		Integer a[] = {0, 1, 2, 3, 3, 3, 4, 5, 6, 7, 8, 9, 10};
		findPairs(a, 9);
	}
}
