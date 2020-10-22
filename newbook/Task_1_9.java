// String Rotation: Assume you have a method isSubstring which checks if one word is a substring
// of another. Given two strings, sl and s2, write code to check if s2 is a rotation of s1 using only one
// call to isSubstring (e.g., "waterbottle" is a rotation of"erbottlewat").
import java.util.*;

public class Task_1_9 {
	static boolean isSubstring(final String s1, final String s2) {
		return s1.indexOf(s2) >= 0;
	}

	static boolean isRotation(final String s1, final String s2) {
		if (s1.length() != s2.length() || s1.equals(s2)) {
			return false;
		}

		return isSubstring(s1 + s1, s2);
	}

	public static void main(String args[]) {
		System.out.println(isRotation("a", "a") == false);
		System.out.println(isRotation("a", "b") == false);
		System.out.println(isRotation("a", "aa") == false);
		System.out.println(isRotation("ab", "ba") == true);
		System.out.println(isRotation("abcde", "cdeab") == true);
		System.out.println(isRotation("rotation", "ionrotat") == true);
	}
}
