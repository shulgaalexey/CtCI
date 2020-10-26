// Permutations with Dups: Write a method to compute all permutations of a string whose characters
// are not necessarily unique. The list of permutations should not have duplicates.
import java.util.*;

public class Task_8_8 {

	static Map<Character, Integer> buildCharFreq(String str) {
		Map<Character, Integer> freq = new HashMap<>();
		for (int i = 0; i < str.length(); i++) {
			Character c = str.charAt(i);
			if (!freq.containsKey(c)) {
				freq.put(c, 0);
			}
			freq.put(c, freq.get(c) + 1);
		}
		return freq;
	}

	static void getPerms(String pref, int remaining,  Map<Character, Integer> freq, List<String> result) {
		if (remaining == 0) {
			result.add(pref);
			return;
		}

		for (Character c: freq.keySet()) {
			int count = freq.get(c);
			if (count > 0) {
				freq.put(c, count - 1);
				getPerms(pref + c, remaining - 1, freq, result);
				freq.put(c, count);
			}
		}
	}

	static List<String> getPerms(String str) {
		Map<Character, Integer> freq = buildCharFreq(str);
		List<String> result = new ArrayList<>();
		getPerms("", str.length(), freq, result);
		return result;
	}

	public static void main(String args[]) {
		String str = "aaabbc";
		List<String> perms = getPerms(str);
		System.out.println(perms);

		Set<String> existing = new HashSet<>();
		for (String cur: perms) {
			if (existing.contains(cur)) {
				throw new IllegalStateException("Duplicate");
			}
			existing.add(cur);
		}
		System.out.println("Finish");
	}
}
