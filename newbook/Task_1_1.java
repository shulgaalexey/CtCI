// Is Unique: Implement an algorithm to determine if a string has all unique characters.
// What if you cannot use additional data structures?

import java.util.*;

public class Task_1_1 {

	static boolean isUnique(final String str) {
		if (str == null || str.isEmpty()) {
			return false;
		}

		if (str.length() == 1) {
			return true;
		}

		if (str.length() > 26) {
			return true;
		}

		boolean[] arr = new boolean[26];

		for (int i = 0; i < str.length(); i++) {
			int charCode = str.charAt(i) - 'a';
			if (arr[charCode]) {
				return false;
			}
			arr[charCode] = true;
		}
		return true;
	}

	static boolean isUniqueNoExtraDS(final String str) {
		if (str == null || str.isEmpty()) {
			return false;
		}

		if (str.length() == 1) {
			return true;
		}

		if (str.length() > 26) {
			return true;
		}

		for (int i = 0; i < (str.length() - 1); i++) {
			for (int j = i + 1; j < str.length(); j++) {
				if (str.charAt(i) == str.charAt(j)) {
					return false;
				}
			}
		}
		return true;
	}

	static boolean isUniqueNoExtraDSFaster(final String str) {
		if (str == null || str.isEmpty()) {
			return false;
		}

		if (str.length() == 1) {
			return true;
		}

		if (str.length() > 26) {
			return true;
		}

		char[] arr = new char[str.length()];

		for (int i = 0; i < str.length(); i++) {
			arr[i] = str.charAt(i);
		}

		Arrays.sort(arr);

		for (int i = 0; i < (str.length() - 1); i++) {
			if(arr[i] == arr[i + 1]) {
				return false;
			}
		}

		return true;
	}

	public static void main(String args[]) {
		System.out.println(isUnique(null) == false);
		System.out.println(isUnique("") == false);
		System.out.println(isUnique("a") == true);
		System.out.println(isUnique("ab") == true);
		System.out.println(isUnique("aa") == false);
		System.out.println(isUnique("aba") == false);

		System.out.println(isUniqueNoExtraDS(null) == false);
		System.out.println(isUniqueNoExtraDS("") == false);
		System.out.println(isUniqueNoExtraDS("a") == true);
		System.out.println(isUniqueNoExtraDS("ab") == true);
		System.out.println(isUniqueNoExtraDS("aa") == false);
		System.out.println(isUniqueNoExtraDS("aba") == false);

		System.out.println(isUniqueNoExtraDSFaster(null) == false);
		System.out.println(isUniqueNoExtraDSFaster("") == false);
		System.out.println(isUniqueNoExtraDSFaster("a") == true);
		System.out.println(isUniqueNoExtraDSFaster("ab") == true);
		System.out.println(isUniqueNoExtraDSFaster("aa") == false);
		System.out.println(isUniqueNoExtraDSFaster("aba") == false);
	}
}
