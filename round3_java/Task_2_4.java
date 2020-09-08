// 2.4 Write a code to partition a linked list around a value x, such that all nodes less than x,
// come before all nodes grater than or equal to x.
//
// Quite interesting
// Can be asked in addition to Quic Sort algorithm
//
import java.util.*;

public class Task_2_4 {

	static class List {
		int val;
		List next;
		List(int val) {
			this.val = val;
			this.next = null;
		}
	}

	static List partition(List l, int x) {
		List small = null;
		List big = null;

		while (l != null) {
			System.out.println(l.val);
			List next = l.next;
			if (l.val < x) {
				if (small == null) {
					small = l;
					l.next = null;
				} else {
					l.next = small;
					small = l;
				}
			} else {
				if (big == null) {
					big = l;
					l.next = null;
				} else {
					l.next = big;
					big = l;
				}
			}
			l = next;
		}

		if (small == null) {
			return big;
		}

		List smallHead = small;
		while (smallHead.next != null) {
			smallHead = smallHead.next;
		}
		smallHead.next = big;
		return small;
	}

	public static void main(String args[]) {
		List l = new List(5);
		l.next = new List(1);
		l.next.next = new List(2);
		l.next.next.next = new List(4);
		l.next.next.next.next = new List(3);

		l = partition(l, 3);

		System.out.println("partitioned:");
		int cnt = 10;
		while (l != null && cnt --> 0) {
			System.out.println(l.val);
			l = l.next;
		}

	}
}
