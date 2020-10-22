// Sum Lists: You have two numbers represented by a linked list, where each node contains a single
// digit. The digits are stored in reverse order, such that the 1 's digit is at the head of the list. Write a
// function that adds the two numbers and returns the sum as a linked list.
// EXAMPLE
// Input: (7-> 1 -> 6) + (5 -> 9 -> 2).That is,617 + 295.
// Output: 2 -> 1 -> 9. That is, 912.
// FOLLOW UP
// Suppose the digits are stored in forward order. Repeat the above problem.
// EXAMPLE
// lnput:(6 -> 1 -> 7) + (2 -> 9 -> 5).That is,617 + 295.
// Output: 9 -> 1 -> 2. That is, 912.
import java.util.*;

public class Task_2_5 {
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

	static MyList add_reverse(MyList l1, MyList l2) {
		MyList sum = null;
		MyList sumHead = null;
		int buf = 0;
		while (l1 != null || l2 != null) {
			final int n = buf
				+ ((l1 != null) ? l1.data : 0)
				+ ((l2 != null) ? l2.data : 0);
			final int digit = n % 10;
			buf = n / 10;
			if (sum == null) {
				sum = new MyList(digit);
				sumHead = sum;
			} else {
				sum.next = new MyList(digit);
				sum = sum.next;
			}
			l1 = (l1 != null) ? l1.next : null;
			l2 = (l2 != null) ? l2.next : null;
		}
		return sumHead;
	}

	static int buf = 0;

	static MyList add(MyList l1, MyList l2) {

		// TODO add zeroes to make lists the same length

		buf = 0;
		MyList tail = getSumTail(l1.next, l2.next);
		int n = l1.data + l2.data + buf;
		MyList res = new MyList(n % 10);
		res.next = tail;
		if (n / 10 > 0) {
			MyList extra = new MyList(n/ 10);
			extra.next = res;
			res = extra;
		}
		return res;
	}

	static MyList getSumTail(MyList l1, MyList l2) {
		if (l1 == null && l2 == null) {
			return null;
		}

		MyList tail = getSumTail(l1.next, l2.next);
		int tailBuf = buf;

		int n = (l1 != null) ? l1.data : 0;
		n += (l2 != null) ? l2.data : 0;
		n += tailBuf;
		buf = n / 10;

		MyList res = new MyList(n % 10);
		res.next = tail;

		return res;
	}

	public static void main(String args[]) {
		MyList l1 = new MyList(7);
		l1.next = new MyList(1);
		l1.next.next = new MyList(6);

		MyList l2 = new MyList(5);
		l2.next = new MyList(9);
		l2.next.next = new MyList(2);

		print(add_reverse(l1, l2));	// 2 1 9

		System.out.println("---------------------------------");

		MyList l3 = new MyList(6);
		l3.next = new MyList(1);
		l3.next.next = new MyList(7);

		MyList l4 = new MyList(2);
		l4.next = new MyList(9);
		l4.next.next = new MyList(5);

		print(add(l3, l4));	// 9 1 2

		System.out.println("---------------------------------");

		MyList l5 = new MyList(9);
		l5.next = new MyList(7);
		l5.next.next = new MyList(8);

		MyList l6 = new MyList(6);
		l6.next = new MyList(8);
		l6.next.next = new MyList(5);

		print(add(l5, l6));  // 1 6 6 3

	}
}
