// Parens: Implement an algorithm to print all valid (e.g., properly opened and closed) combinations
// of n pairs of parentheses.
// EXAMPLE
// Input: 3
// Output: ( ( () ) ) , ( () () ) , ( () ) () , () ( () ) , () () ()
import java.util.*;

public class Task_8_9 {
	static void getParens(int leftRemain, int rightRemain,
			String prefix, List<String> results) {
		if (leftRemain < 0 || rightRemain < leftRemain) {
			return;
		}
		if (leftRemain == 0 && rightRemain == 0) {
			results.add(prefix);
			return;
		}
		getParens(leftRemain - 1, rightRemain, prefix + '(', results);
		getParens(leftRemain, rightRemain - 1, prefix + ')', results);
	}
	static List<String> getParens(int n) {
		List<String> results = new ArrayList<>();
		getParens(n, n, "", results);
		return results;
	}
	public static void main(String args[]) {
		System.out.println(getParens(3));
	}
}
