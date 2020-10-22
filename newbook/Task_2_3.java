// Delete Middle Node: Implement an algorithm to delete a node in the middle (i.e., any node but
// the first and last node, not necessarily the exact middle) of a singly linked list, given only access to
// that node.
// EXAMPLE
// lnput:the node c from the linked lista->b->c->d->e->f
// Result: nothing is returned, but the new linked list looks like a->b->d->e->f
import java.util.*;

public class Task_2_3 {
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

	static void delete(MyList l) {
		l.data = l.next.data;
		l.next = l.next.next;
	}

	public static void main(String args[]) {
		MyList l = new MyList('a');
		l.next = new MyList('b');
		l.next.next = new MyList('c');
		l.next.next.next = new MyList('d');
		l.next.next.next.next = new MyList('e');
		l.next.next.next.next.next = new MyList('f');

		print(l);

		delete(l.next.next);

		print(l);

	}
}
