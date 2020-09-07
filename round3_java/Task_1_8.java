// 1.8 Assume you have a method isSubstring which checks if one word is a substring of another.
// Given two strings, s1 and s2, write code to check if s2 is a rotation on s1
// using only one call to isSubstring
// (e.g. "waterbottle" is a rotation of "erbottlewat")
import java.util.*;

public class Task_1_8 {
	static boolean isSubstring(String s1, String s2) {
		return s1.contains(s2);
	}

	static boolean isRotation(String s1, String s2) {
		if (s1.length() != s2.length()) {
			return false;
		}
		return isSubstring(s1 + s1, s2);
	}

	public static void main(String args[]) {
		// "waterbottle"  "erbottlewat"
		// "waterbottle"  "erbottle_waterbottle_wat"
		System.out.println(isRotation("waterbottle", "erbottlewat") == true);

		System.out.println(isRotation("waterbottla", "erbottlewat") == false);
	}
}
