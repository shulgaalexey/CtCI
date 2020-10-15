// Check Permutations: Given two strings, write a method to decide if one is a permutation of the other.
import java.util.*;

public class Task_1_2 {

	static boolean isPerm_NlogN(final String str1, final String str2) {
		if (str1 == null || str2 == null || str1.isEmpty() || str2.isEmpty()) {
			return false;
		}

		if (str1.length() != str2.length()) {
			return false;
		}

		char[] arr1 = new char[str1.length()];
		char[] arr2 = new char[str1.length()];

		for (int i = 0; i < str1.length(); i++) {
			arr1[i] = str1.charAt(i);
			arr2[i] = str2.charAt(i);
		}

		Arrays.sort(arr1);
		Arrays.sort(arr2);

		for (int i = 0; i < arr1.length; i++) {
			if (arr1[i] != arr2[i]) {
				return false;
			}
		}


		return true;
	}

	static boolean isPerm_N(final String str1, final String str2) {
		if (str1 == null || str2 == null || str1.isEmpty() || str2.isEmpty()) {
			return false;
		}

		if (str1.length() != str2.length()) {
			return false;
		}

		Map<Character, Integer> m = new HashMap<>();


		for (int i = 0; i < str1.length(); i++) {
			final Character c = str1.charAt(i);
			if (!m.containsKey(c)) {
				m.put(c, 0);
			}
			m.put(c, m.get(c) + 1);
		}


		for (int i = 0; i < str2.length(); i++) {
			final Character c = str2.charAt(i);
			if (!m.containsKey(c)) {
				return false;
			}
			m.put(c, m.get(c) - 1);
			if (m.get(c) < 0) {
				return false;
			}
		}


		return true;
	}

	public static void main(String args[]) {
		System.out.println(isPerm_NlogN(null, null) == false);
		System.out.println(isPerm_NlogN("", "") == false);
		System.out.println(isPerm_NlogN("a", "a") == true);
		System.out.println(isPerm_NlogN("aa", "aa") == true);
		System.out.println(isPerm_NlogN("ab", "ba") == true);
		System.out.println(isPerm_NlogN("aba", "aba") == true);
		System.out.println(isPerm_NlogN("aba", "baa") == true);
		System.out.println(isPerm_NlogN("aba", "bab") == false);
		System.out.println(isPerm_NlogN("aba", "ba") == false);

		System.out.println(isPerm_N(null, null) == false);
		System.out.println(isPerm_N("", "") == false);
		System.out.println(isPerm_N("a", "a") == true);
		System.out.println(isPerm_N("aa", "aa") == true);
		System.out.println(isPerm_N("ab", "ba") == true);
		System.out.println(isPerm_N("aba", "aba") == true);
		System.out.println(isPerm_N("aba", "baa") == true);
		System.out.println(isPerm_N("aba", "bab") == false);
		System.out.println(isPerm_N("aba", "ba") == false);

	}
}
