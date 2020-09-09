// Quite interesting
// It's about recursion
//
// 2.5 You have two numbers represented by a linked list, where each node contains a single digit.
// The digits are stored in reverse order, such that the 1's digit is at the head of the list.
// Write a function that adds the two numbers and returns the sum as  a linked list.
// EXAMPLE
// Input: (7->1->6) + (5->9->2). That is 617 + 295.
// Output: 2->1->9. that is 912.
// FOLLOW UP
// Suppose the digits are stored in forward order. Repeat the above problem.
// EXAMPLE
// Input: (6->1->7) + (2->9->5). that is 617 + 295.
// Output: 9->1->2. That is 912.
import java.util.*;

public class Task_2_5 {
	static class List {
		int val;
		List next;
		List(int val) {
			this.val = val;
			this.next = null;
		}
	}

	static List add(List l1, List l2) {
		List resHead = null;
		List resTail = null;
		int buf = 0;
		while (l1 != null || l2 != null) {
			int sum = buf;
		    if (l1 != null) {
				sum += l1.val;
			}
			if (l2 != null) {
				sum += l2.val;
			}
			buf = sum / 10;
			List newItem = new List(sum % 10);
			if (resHead == null) {
				resHead = newItem;
				resTail = resHead;
			} else {
				resTail.next = newItem;
				resTail = resTail.next;
			}
			if (l1 != null) {
				l1 = l1.next;
			}
			if (l2 != null) {
				l2 = l2.next;
			}
		}

		return resHead;
	}


	static int buf = 0;
	static List resHead = null;

	static List addForward(List l1, List l2) {
		// TODO make list the same length by adding zeroes in the head of the shorter one

		doAddForward(l1, l2);
		if (buf > 0) {
			List newItem = new List(buf);
			newItem.next = resHead;
			resHead = newItem;
		}
		return resHead;
	}

	static void doAddForward(List l1, List l2) {
		if (l1.next == null) {	// l2.next is null here as well
			int sum = l1.val + l2.val;
			buf = sum / 10;
			resHead = new List(sum % 10);
		} else {
			doAddForward(l1.next, l2.next);
			int sum = buf + l1.val + l2.val;
			buf = sum / 10;
			List newItem = new List(sum % 10);
			newItem.next = resHead;
			resHead = newItem;
		}
	}

	static void print(List l) {
		while (l != null) {
			System.out.println(l.val);
			l = l.next;
		}
	}

	public static void main(String args[]) {
		{ // Backward list
			// Input: (7->1->6) + (5->9->2). That is 617 + 295.
			// Output: 2->1->9. that is 912.
			List l1 = new List(7);
			l1.next = new List(1);
			l1.next.next = new List(6);

			List l2 = new List(5);
			l2.next = new List(9);
			l2.next.next = new List(2);

			List res = add(l1, l2);
			print(res);
		}

		System.out.println("---------");

		{ // Forward list
			// Input: (6->1->7) + (2->9->5). that is 617 + 295.
			// Output: 9->1->2. That is 912.
			List l1 = new List(6);
			l1.next = new List(1);
			l1.next.next = new List(7);

			List l2 = new List(2);
			l2.next = new List(9);
			l2.next.next = new List(5);

			List res = addForward(l1, l2);
			print(res);
		}
	}
}
