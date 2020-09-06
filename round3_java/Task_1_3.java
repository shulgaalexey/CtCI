// 1.3 Given two strings, write a method to decide if one is a permutation of the other.

import java.util.*;

class Task_1_3 {
	static boolean isPermutation(final String str1, final String str2) {
		if (str1 == null || str2 == null || str1.isEmpty() || str2.isEmpty()) {
			return false;
		}
		if (str1.length() != str2.length()) {
			return false;
		}

		Map<Character, Integer> m = new HashMap();
		for (int i = 0; i < str1.length(); i++) {
			final Character c = str1.charAt(i);
			if (!m.containsKey(c)) {
				m.put(c, 1);
			} else {
				m.put(c, m.get(c) + 1);
			}
		}
		for (int i = 0; i < str2.length(); i++) {
			final Character c = str2.charAt(i);
			if (!m.containsKey(c)) {
				return false;
			}
			m.put(c, m.get(c) - 1);
		}

		for (Map.Entry<Character, Integer> e: m.entrySet()) {
			if (e.getValue() != 0) {
				return false;
			}
		}

		return true;
	}

	static boolean isPermutation2(final String str1, final String str2) {
		if (str1 == null || str2 == null || str1.isEmpty() || str2.isEmpty()) {
			return false;
		}
		if (str1.length() != str2.length()) {
			return false;
		}
		byte [] a1 = str1.getBytes();
		byte [] a2 = str2.getBytes();
		Arrays.sort(a1);
		Arrays.sort(a2);

		for (int i = 0; i < a1.length; i++) {
			if (a1[i] != a2[i]) {
				return false;
			}
		}
		return true;
	}

	public static void main(String args[]) {
		System.out.println("First approach:");
		System.out.println(isPermutation("", "") == false);
		System.out.println(isPermutation(null, null) == false);
		System.out.println(isPermutation("a", "a") == true);
		System.out.println(isPermutation("a", "b") == false);
		System.out.println(isPermutation("ab", "ba") == true);
		System.out.println(isPermutation("aa", "aa") == true);
		System.out.println(isPermutation("aa", "a") == false);
		System.out.println(isPermutation("aab", "abb") == false);

		System.out.println("Second approach:");

		System.out.println(isPermutation2("", "") == false);
		System.out.println(isPermutation2(null, null) == false);
		System.out.println(isPermutation2("a", "a") == true);
		System.out.println(isPermutation2("a", "b") == false);
		System.out.println(isPermutation2("ab", "ba") == true);
		System.out.println(isPermutation2("aa", "aa") == true);
		System.out.println(isPermutation2("aa", "a") == false);
		System.out.println(isPermutation2("aab", "abb") == false);

		System.out.println("Done");
	}
}

