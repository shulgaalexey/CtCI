// Permutations without Dups: Write a method to compute all permutations of a string of unique
// characters.
import java.util.*;

public class Task_8_7 {
	static List<String> getPerms(String str) {
		List<String> result = new ArrayList<>();
		if (str.isEmpty()) {
			result.add("");
			return result;
		}

		char c = str.charAt(0);
		List<String> prev = getPerms(str.substring(1));
		for (String cur: prev) {
			for (int i = 0; i < cur.length(); i++) {
				StringBuilder sb = new StringBuilder(cur);
				sb.insert(i, c);
				result.add(sb.toString());
			}
			String sLast = cur + c;
			result.add(sLast);
		}
		return result;
	}
	public static void main(String args[]) {
		String str = "abcd";
		List<String> perms = getPerms(str);
		System.out.println(perms);

		Set<String> existing = new HashSet<>();
		for (String s: perms) {
			System.out.println(s);
			if (existing.contains(s)) {
				System.out.println("Duplication: " + s);
			}
			existing.add(s);
		}

		System.out.println("Finish");
	}
}
