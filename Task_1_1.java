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


	public static void main(String args[]) {
		System.out.println(uniqChars(null) == false);
		System.out.println(uniqChars("") == false);
		System.out.println(uniqChars("a") == true);
		System.out.println(uniqChars("aa") == false);
		System.out.println(uniqChars("ab") == true);
		System.out.println(uniqChars("aba") == false);
		System.out.println(uniqChars("abyz") == true);
		System.out.println("done");
	}

}
