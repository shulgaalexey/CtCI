// 2.1 Write code to remove duplicates from unsorted list.
// FOLLOW UP
// How would you solve this problem if a temporary buffer is not allowed?
import java.util.*;

public class Task_2_1 {

	static class List {
		char val;
		List next;
		List(char val) {
			this.val = val;
			this.next = null;
		}
	}

	static void remove_dups_fast(List l) {
		final List head = l;
		Set<Character> s = new HashSet<>();
		while (l != null) {
			s.add(l.val);
			l = l.next;
		}

		l = head;
		List prev = null;
		while (l != null) {
			if (s.contains(l.val)) {
				s.remove(l.val);
				prev = l;
			} else {
				prev.next = l.next;
			}
			l = l.next;
		}
	}

	static void remove_dups(List l) {
		final List head = l;
		while (l != null) {
			List ptr = l.next;
			List prev = l;
			while (ptr != null) {
				if (ptr.val == l.val) {
					prev.next = ptr.next;
				} else {
					prev = ptr;
				}
				ptr = ptr.next;
			}
			l = l.next;
		}
	}

	static void print(List l) {
		while (l != null) {
			System.out.print(" " + l.val);
			l = l.next;
		}
		System.out.println();
	}

	static List generate() {
		List l = new List('a');
		l.next = new List('b');
		l.next.next = new List('c');
		l.next.next.next = new List('b');
		l.next.next.next.next = new List('d');
		l.next.next.next.next.next = new List('c');
		l.next.next.next.next.next.next = new List('a');
		l.next.next.next.next.next.next.next = new List('e');
		return l;
	}

	public static void main(String args[]) {
		List l1 = generate();
		System.out.println("Initial list");
		print(l1);

		System.out.println("Dedupped (fast) list");
		remove_dups_fast(l1);
		print(l1);

		List l2 = generate();
		System.out.println("Dedupped list");
		remove_dups(l2);
		print(l2);
	}
}
