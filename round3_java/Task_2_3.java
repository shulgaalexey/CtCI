// 2.3 Implement an algorithm to delete a node in the middle of a singly linked list, given only access to that node.
// EXAMPLE
// Input: the node c from the linked list a->b->c->d->e
// Result: nothing is returned, but the new linked list lools like a->b->d->e
import java.util.*;

public class Task_2_3 {

	static class List {
		char val;
		List next;
		List(char val) {
			this.val = val;
			this.next = next;
		}
	}

	static void deleteNode(List n) {
		while (n != null && n.next != null) {
			n.val = n.next.val;
			n.next = n.next.next;
			n = n.next;
		}
	}

	public static void main(String args[]) {
		List l = new List('a');
		l.next = new List('b');
		l.next.next = new List('c');
		l.next.next.next = new List('d');
		l.next.next.next.next = new List('e');

		deleteNode(l.next.next);	// Delete 'c'

		while (l != null) {
			System.out.println(l.val);
			l = l.next;
		}
	}
}
