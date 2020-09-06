// 1.5 Inplement a method to perform basic string compression using the counts
// of repeated characters. For example, the string aabcccccaaa would become a2b1c5a3.
// If the "compressed" string would not become smaller than the original string,
// your method should return the original string.
// You can assume the string has only uper and lower case letters (a-z)
import java.util.*;

public class Task_1_5 {
	static String compress(final String str) {
		String res = "";
		char cur = str.charAt(0);
		int cnt = 1;
		for (int i = 1; i < str.length(); i++) {
			if (str.charAt(i) == cur) {
				cnt ++;
			} else {
				res += cur;
				res += cnt;
				cur = str.charAt(i);
				cnt = 1;
			}
		}
		res += cur;
		res += cnt;
		return (res.length() < str.length()) ? res : str;
	}

	public static void main(String args[]) {
		System.out.println(compress("a").equals("a"));
		System.out.println(compress("aa").equals("aa"));
		System.out.println(compress("aaa").equals("a3"));
		System.out.println(compress("aabc").equals("aabc"));
		System.out.println(compress("aabcccccaaa").equals("a2b1c5a3"));
	}

}
