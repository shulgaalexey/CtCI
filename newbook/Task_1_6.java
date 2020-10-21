// String Compression: Implement a method to perform basic string compression using the counts
// of repeated characters. For example, the string aabcccccaaa would become a2b1c5a3. If the
// "compressed" string would not become smaller than the original string, your method should return
// the original string. You can assume the string has only uppercase and lowercase letters (a - z).
import java.util.*;

public class Task_1_6 {

	static String compress(String str) {
		StringBuilder sb = new StringBuilder();
		char c = str.charAt(0);
		int n = 1;
		int len = 1;
		for (int i = 1; i < str.length(); i++) {
			if (str.charAt(i) != c) {
				sb.append(c);
				sb.append(n);
				c = str.charAt(i);
				n = 1;
				len += 1 + ("" + n).length();
				if (len >= str.length()) {
					return str;
				}
			} else {
				n++;
			}
		}
		sb.append(c);
		sb.append(n);
		len += 1 + ("" + n).length();
		if (len >= str.length()) {
			return str;
		}
		return sb.toString();
	}

	public static void main(String args[]) {
		System.out.println(compress("aabcccccaaa").equals("a2b1c5a3"));
		System.out.println(compress("abc").equals("abc"));
	}
}
