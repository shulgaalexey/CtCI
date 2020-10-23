// Loop Detection: Given a circular linked list, implement an algorithm that returns the node at the
// beginning of the loop.
// DEFINITION
// Circular linked list: A (corrupt) linked list in which a node's next pointer points to an earlier node, so
// as to make a loop in the linked list.
// EXAMPLE
// Input: A -> B -> C -> D -> E -> C [the same C as earlier]
// Output: C
import java.util.*;

public class Task_2_8 {
	static class MyList {
		char data;
		MyList next;
		MyList(char data) {
			this.data = data;
		}
	}

	public static void main(String args[]) {
		MyList A = new MyList('A');
		MyList B = new MyList('B');
		MyList C = new MyList('C');
		MyList D = new MyList('D');
		MyList E = new MyList('E');

		MyList l = A;
		A.next = B;
		B.next = C;
		C.next = D;
		D.next = E;
		E.next = C;

		// Find collision
		MyList fast = l;
		MyList slow = l;
		while (true) {
			slow = slow.next;
			fast = fast.next.next;
			if (slow == fast) {
				break;
			}
		}

		// Find accurate start of the loop
		slow = l;
		while (true) {
			if (slow == fast) {
				System.out.println(slow.data); // Must be 'C'
				return;
			}
			slow = slow.next;
			fast = fast.next;
		}
	}
}
