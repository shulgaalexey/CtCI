// Implement a function void reverse(char *str) in C or C++ which reverses a null-terminated string

import java.util.*;

public class Task_1_2 {
	static String reverse(final String str) {
		if (str == null || str.isEmpty()) {
			return str;
		}

		byte [] bytes = str.getBytes();
		final int n = str.length();
		for (int i = 0; i < (n / 2); i ++) {
			byte b = bytes[i];
			bytes[i] = bytes[n - i - 1];
			bytes[n - i - 1] = b;
		}
		return new String(bytes);
	}

	public static void main(String args[]) {
		System.out.println(reverse("").equals(""));
		System.out.println(reverse("a").equals("a"));
		System.out.println(reverse("ab").equals("ba"));
		System.out.println(reverse("abc").equals("cba"));
		System.out.println(reverse("abcde").equals("edcba"));
	}
}
