// URLify: Write a method to replace all spaces in string with '%20'. You may assume that the string
// has sufficient space at the end to hold the additional characters, and that you are given the "true"
// length of the string. (Note: If implementing in Java, please use a character array so that you can
// perform this operation in place.)
// EXAMPLE
// Input:  "Mr John Smith    ", 13
// Output: "Mr%20John%20Smith", 13

import java.util.*;

public class Task_1_2 {
	static void urlify(final char arr[], int trueSize) {
		int p1 = arr.length - 1;
		int p2 = trueSize - 1;
		while (p2 >= 0) {
			if (arr[p2] != ' ') {
				arr[p1] = arr[p2];
				p1--;
				p2--;
			} else {
				arr[p1] = '0';
				arr[p1 - 1] = '2';
				arr[p1 - 2] = '%';
				p1 -= 3;
				p2 --;
			}
		}
	}

	public static void main(String args[]) {
		final String str ="Mr John Smith    ";
		char[] arr = new char[str.length()];
		for (int i = 0; i < str.length(); i++) {
			arr[i] = str.charAt(i);
		}

		urlify(arr, 13);
		System.out.println(arr);
		System.out.println("Mr%20John%20Smith");
	}
}
