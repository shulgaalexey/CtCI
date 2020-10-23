// Palindrome: Implement a function to check if a linked list is a palindrome
import java.util.*;

public class Task_2_6 {
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

	static MyList revert(MyList l) {
		MyList revert = null;
		while (l != null) {
			if (revert == null) {
				revert = new MyList(l.data);
			} else {
				MyList newItem = new MyList(l.data);
				newItem.next = revert;
				revert = newItem;
			}
			l = l.next;
		}
		return revert;
	}

	static boolean isPalindrome(MyList l) {
		MyList revert = revert(l);
		print(l);
		print(revert);

		while(l != null) {
			if (l.data != revert.data) {
				return false;
			}
			l = l.next;
			revert = revert.next;
		}
		return revert == null;
	}

	public static void main(String args[]) {
		MyList l = new MyList('a');
		l.next = new MyList('b');
		l.next.next = new MyList('c');
		l.next.next.next = new MyList('b');
		l.next.next.next.next = new MyList('a');

		System.out.println(isPalindrome(l) == true);
		System.out.println(isPalindrome(l.next) == false);

	}
}
