// Power Set: Write a method to return all subsets of a set.
import java.util.*;

public class Task_8_4 {

	static ArrayList<HashSet<String>> doSubsetsRecursive(List<String> s, int index) {
		ArrayList<HashSet<String>> sets = new ArrayList<HashSet<String>>();
		if (s.size() == index) {
			sets.add(new HashSet<>());
		} else {
			sets = doSubsetsRecursive(s, index + 1);
			String item = s.get(index);
			List<HashSet<String>> moreSets = new ArrayList<HashSet<String>>();
			for (HashSet<String> subset: sets) {
				HashSet<String> newSubset = new HashSet<>();
				newSubset.addAll(subset);
				newSubset.add(item);
				moreSets.add(newSubset);
			}
			sets.addAll(moreSets);
		}
		return sets;
	}

	static ArrayList<HashSet<String>> subsetsRecursive(Set<String> s) {
		List<String> arr = new ArrayList<>();
		for (String str: s) {
			arr.add(str);
		}
		return doSubsetsRecursive(arr, 0);
	}

	static List<HashSet<String>> subsets(Set<String> s) {
		List<String> arr = new ArrayList<>();
		List<Boolean> bits = new ArrayList<>();
		for (String str: s) {
			arr.add(str);
			bits.add(false);
		}

		int setCnt = 1;
		for (int i = 0; i < s.size(); i++) {
			setCnt *= 2;
		}

		List<HashSet<String>> sets = new ArrayList<HashSet<String>>();
		for (int i = 0; i < setCnt; i++) {
			HashSet<String> set = new HashSet<>();
			for (int j = 0; j < bits.size(); j++) {
				if (bits.get(j)) {
					set.add(arr.get(j));
				}
			}
			sets.add(set);

			int j = bits.size() - 1;
			boolean carry = false;
			do {
				if (bits.get(j) == false) {
					bits.set(j, true);
					break;
				} else {
					bits.set(j, false);
					carry = true;
					j--;
				}
			} while(carry && j >= 0);
		}
		return sets;
	}

	public static void main(String args[]) {
		Set<String> set = new HashSet<>();
		set.add("A");
		set.add("B");
		set.add("C");
		set.add("D");
		//set.add("E");
		//set.add("F");
		List<HashSet<String>> sets = subsets(set);
		for (HashSet<String> s: sets) {
			System.out.println(s);
		}
		System.out.println("-------------");
		List<HashSet<String>> setRec = subsetsRecursive(set);
		for (HashSet<String> s: setRec) {
			System.out.println(s);
		}
	}
}
