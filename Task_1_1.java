/**
 * Implement an algorithm to determine if a string has all unique characters.
 * What if you cannot use additional data structures
 */
import java.util.*;

public class Task_1_1 {

	// Only lower-case [a-z]
	static boolean uniqChars(final String str) {
		if (str == null || str.isEmpty()) {
			return false;
		}
		boolean [] existing = new boolean[26];
		final byte [] strBytes = str.getBytes();
		final byte a = (byte) 'a';
		for (int i = 0; i < strBytes.length; i++) {
			int b = strBytes[i] - a;
			if (existing[b]) {
				return false;
			}
			existing[b] = true;
		}
		return true;
	}

	static boolean uniqCharsNoDataStructure(final String str) {
		if (str == null || str.isEmpty()) {
			return false;
		}

		for (int i = 0; i < str.length(); i++) {
			for (int j = i + 1; j < str.length(); j++) {
				if (str.charAt(i) == str.charAt(j)) {
					return false;
				}
			}
		}
		return true;

	}


	public static void main(String args[]) {
		System.out.println("With array");
		System.out.println(uniqChars(null) == false);
		System.out.println(uniqChars("") == false);
		System.out.println(uniqChars("a") == true);
		System.out.println(uniqChars("aa") == false);
		System.out.println(uniqChars("ab") == true);
		System.out.println(uniqChars("aba") == false);
		System.out.println(uniqChars("abyz") == true);

		System.out.println("No additional data structure");
		System.out.println(uniqCharsNoDataStructure(null) == false);
		System.out.println(uniqCharsNoDataStructure("") == false);
		System.out.println(uniqCharsNoDataStructure("a") == true);
		System.out.println(uniqCharsNoDataStructure("aa") == false);
		System.out.println(uniqCharsNoDataStructure("ab") == true);
		System.out.println(uniqCharsNoDataStructure("aba") == false);
		System.out.println(uniqCharsNoDataStructure("abyz") == true);

		System.out.println("done");
	}

}
