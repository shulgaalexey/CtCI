// 2.7 Implement a function to check if a linked list a palindrome.
import java.util.*;

public class Task_2_7 {
	static class List {
		char val;
		List next;
		List(char val) {
			this.val = val;
			this.next = next;
		}
	}

	static boolean isPal = false;
	static List headPtr = null;
	static List tailPtr = null;

	static boolean isPalindrome(List l) {
		headPtr = l;
		doRecursion(l.next, l);
		return isPal;
	}

	static void doRecursion(List prev, List cur) {
		// TODO add shortcut when isPal is false
		if (cur.next == null) {
			tailPtr = cur;	// Now we know where is the end of the list
			isPal = headPtr.val == tailPtr.val;
			headPtr = headPtr.next;
			tailPtr = prev;
		} else {
			doRecursion(cur, cur.next);
			isPal &= headPtr.val == tailPtr.val;
			headPtr = headPtr.next;
			tailPtr = prev;
		}
	}

	public static void main(String args[]) {
		List l = new List('a');
		l.next = new List('b');
		l.next.next = new List('c');
		l.next.next.next = new List('b');
		l.next.next.next.next = new List('a');

		System.out.println(isPalindrome(l));
	}
}
