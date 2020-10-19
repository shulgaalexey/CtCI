// One Away: There are three types of edits that can be performed on strings: insert a character,
// remove a character, or replace a character. Given two strings, write a function to check if they are
// one edit (or zero edits) away.
// EXAMPLE
//   pale, ple -> true
//   pales, pale -> true
//   pale, bale -> true
//   pale, bake -> false
import java.util.*;

public class Task_1_5 {

	static boolean onEdition(String s1, String s2) {
		boolean dif = false;
		for (int i = 0; i < s1.length(); i++) {
			if (s1.charAt(i) != s2.charAt(i)) {
				if (!dif) {
					dif = true;
				} else {
					return false;
				}
			}
		}
		return true;
	}

	static boolean onInsertion(String shortStr, String longStr) {
		boolean dif = false;
		for (int i = 0, j = 0; i < shortStr.length(); i++, j++) {
			if (shortStr.charAt(i) != longStr.charAt(j)) {
				if (!dif) {
					dif = true;
					j++;
				} else {
					return false;
				}
			}
		}
		return true;
	}

	static boolean isOneEdit(String s1, String s2) {
		if (s1 == null || s2 == null || s1.isEmpty() || s2.isEmpty()) {
			return false;
		}

		if (s1.equals(s2)) {
			return true;
		}

		if (Math.abs(s1.length() - s2.length()) > 1) {
			return false;
		}

		if (s1.length() == s2.length()) {
			return onEdition(s1, s2);
		} else if (s1.length() < s2.length()) {
			return onInsertion(s1, s2);
		} else {
			return onInsertion(s2, s1);
		}
	}

	public static void main(String args[]) {
		System.out.println(isOneEdit("pale", "ale") == true);
		System.out.println(isOneEdit("pale", "ple") == true);
		System.out.println(isOneEdit("pales", "pale") == true);
		System.out.println(isOneEdit("pale", "bale") == true);
		System.out.println(isOneEdit("pale", "bake") == false);
		System.out.println(isOneEdit("pale", "bakeee") == false);
	}
}
