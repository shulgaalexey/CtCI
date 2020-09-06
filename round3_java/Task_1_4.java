// 1.4 Write a method to replace all spaces in a string with '%20'.
// You may assume that the string has sufficient space at the end of the string
// to hold the additional characters, and that you are given the "true" length of the string.
// (Note: if implementing in Java, please use a character array
// so that you can perform this operation in place.)
// EXAMPLE:
//  Input:  "Mr John Smith    ", 13
//  Output: "Mr%20John%20Smith"

import java.util.*;

public class Task_1_4 {
	static String replaceSpaces(final String str) {
		final int n = str.length();
		Character arr [] = new Character[n];
		for (int i = 0; i < n; i++) {
			arr[i] = str.charAt(i);
		}
		int ptr1 = 0;
		for (int i = n - 1; i >= 0; i--) {
			if (arr[i] != ' ') {
				ptr1 = i;
				break;
			}
		}

		Character res [] = new Character[n];
		int ptr2 = n - 1;
		for (int i = ptr1; i >= 0; i--) {
			if (arr[i] != ' ') {
				res[ptr2 --] = arr[i];
			} else {
				res[ptr2 --] = '0';
				res[ptr2 --] = '2';
				res[ptr2 --] = '%';
			}
		}

		String strRes = "";
		for (int i = 0; i < n; i++) {
			strRes += res[i];
		}
		return strRes;
	}

	public static void main(String args[]) {
		System.out.println(replaceSpaces("Mr John Smith    ").equals("Mr%20John%20Smith"));
		System.out.println(replaceSpaces("public static void main      ").equals("public%20static%20void%20main"));
	}
}
