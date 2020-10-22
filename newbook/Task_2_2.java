// Return Kth to Last: Implement an algorithm to find the kth to last element of a singly linked list.
import java.util.*;

public class Task_2_2 {
	static class MyList {
		char data;
		MyList next;
		MyList(char data) {
			this.data = data;
		}
	}

	public static void main(String args[]) {
		// a b c d e f
		MyList l = new MyList('a');
		l.next = new MyList('b');
		l.next.next = new MyList('c');
		l.next.next.next = new MyList('d');
		l.next.next.next.next = new MyList('e');
		l.next.next.next.next.next = new MyList('f');

		final int k = 3;

		MyList runner = l;
		for (int i = 0; i < k; i++) {
			runner = runner.next;
		}

		while (runner != null) {
			l = l.next;
			runner = runner.next;
		}

		System.out.println(l.data == 'd');
	}
}
