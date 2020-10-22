// Partition: Write code to partition a linked list around a value x, such that all nodes less than x come
// before all nodes greater than or equal to x. If x is contained within the list, the values of x only need
// to be after the elements less than x (see below). The partition element x can appear anywhere in the
// "right partition"; it does not need to appear between the left and right partitions.
// EXAMPLE
// Input:
// Output:
// 3 -> 5 -> 8 -> 5 -> 10 -> 2 -> 1 [partition= 5]
// 3 -> 1 -> 2 -> 10 -> 5 -> 5 -> 8
import java.util.*;

public class Task_2_4 {
	static class MyList {
		int data;
		MyList next;
		MyList(int data) {
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

	static MyList partition(MyList l, int n) {
		MyList small = null;
		MyList smallTail = null;
		MyList big = null;
		MyList bigTail = null;

		while (l != null) {
			MyList next = l.next;
			if (l.data < n) {
				if (small == null) {
					small = l;
					smallTail = l;
				} else {
					l.next = small;
					small = l;
				}
			} else {
				if (big == null) {
					big = l;
					bigTail = l;
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
		if (big == null) {
			return small;
		}
		smallTail.next = big;
		bigTail.next = null;
		return small;
	}

	public static void main(String args[]) {
		MyList l = new MyList(3);
		l.next = new MyList(5);
		l.next.next = new MyList(8);
		l.next.next.next = new MyList(5);
		l.next.next.next.next = new MyList(10);
		l.next.next.next.next.next = new MyList(2);
		l.next.next.next.next.next.next = new MyList(1);

		print(l);
		l = partition(l, 5);
		print(l);
	}
}
