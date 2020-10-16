// Palindrom Permutation: Given a string, write a function to check if it is a permutation of a palindrome.
// A palindrome is a word or phrase that is the same forwards and backwards. A permutation
// is a rearrangement of letters. The palindrome does need to be limited to just dictionary words.
// EXAMPLE
// Input:  Tact Coa
// Output: True (permutations: "taco cat", "acto cta", etc)
import java.util.*;

public class Task_1_4 {
	static boolean isPalindrome(final String str) {
		if (str == null || str.isEmpty()) {
			return false;
		}
		if (str.length() == 1) {
			return true;
		}

		Map<Character, Integer> m = new HashMap<>();
		for (int i = 0; i < str.length(); i++) {
			final Character c = Character.toLowerCase(str.charAt(i));
			if (c == ' ') {
				continue;
			}
			if (m.containsKey(c)) {
				m.put(c, m.get(c) + 1);
			} else {
				m.put(c, 1);
			}
		}

		boolean even = false;
		for (Map.Entry<Character, Integer> entry : m.entrySet()) {
			Integer n = entry.getValue();
			if (n % 2 == 1) {
				if (even) {
					return false;
				}
				even = true;
			}
		}

		return true;
	}

	public static void main(String args[]) {
		System.out.println(isPalindrome(null) == false);
		System.out.println(isPalindrome("") == false);
		System.out.println(isPalindrome("a") == true);
		System.out.println(isPalindrome("a a") == true);
		System.out.println(isPalindrome("a b") == false);
		System.out.println(isPalindrome("Tact Coa") == true);
	}
}
