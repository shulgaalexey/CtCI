// Remove Dups: Write code to remove duplicates from an unsorted linked list.
// FOLLOW UP
// How would you solve this problem if a temporary buffer is not allowed?
import java.util.*;

public class Task_2_1 {
	static class MyList {
		char data;
		MyList next;
		MyList(char data) {
			this.data = data;
		}
	}

	static void print(MyList l) {
		while (l != null) {
			System.out.print(l.data + " ");
			l = l.next;
		}
		System.out.println();
	}

	static void dedup(MyList l) {
		Set<Character> s = new HashSet<>();
		MyList cur = l;
		s.add(cur.data);
		while (cur.next != null) {
			if (s.contains(cur.next.data)) {
				cur.next = cur.next.next;
			} else {
				cur = cur.next;
				s.add(cur.data);
			}
		}
	}

	static boolean search(MyList from, MyList to, char data) {
		while (from != to) {
			if (from.data == data) {
				return true;
			}
			from = from.next;
		}
		return false;
	}

	static void dedupNoBuffer(MyList l) {
		MyList head = l;
		while (l.next != null) {
			if (search(head, l.next, l.next.data)) {
				l.next = l.next.next;
			} else {
				l = l.next;
			}
		}
	}

	public static void main(String args[]) {
		MyList l = new MyList('a');
		l.next = new MyList('b');
		l.next.next = new MyList('c');
		l.next.next.next = new MyList('a');
		l.next.next.next.next = new MyList('a');
		l.next.next.next.next.next = new MyList('d');

		print(l);

		//dedup(l);
		dedupNoBuffer(l);

		print(l);
	}
}
