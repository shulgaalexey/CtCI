// Intersection: Given two (singly) linked lists, determine if the two lists intersect.
// Return the intersecting node. Note that the intersection is defined based on reference, not value.
// That is, if the kth node of the first linked list is the exact same node (by reference)
// as the jth node of the second linked list, then they are intersecting.
import java.util.*;

public class Task_2_7 {
	static class MyList {
		char data;
		MyList next;
		MyList(char data) {
			this.data = data;
		}
	}

	static void print(MyList l) {
		MyList head = l;
		while (l != null) {
			System.out.print(l.data + " ");
			l = l.next;
			if (l == head) {
				break;
			}
		}
		System.out.println();
	}

	public static void main(String args[]) {

		MyList n1 = new MyList('1');
		MyList n2 = new MyList('2');
		MyList n9 = new MyList('9');
		MyList n3 = new MyList('3');
		MyList n4 = new MyList('4');
		MyList a = new MyList('a');
		MyList b = new MyList('b');
		MyList X = new MyList('X');
		MyList Y = new MyList('Y');
		MyList Z = new MyList('Z');

		MyList l1 = n1;
		n1.next = n2;
		n2.next = n9;
		n9.next = n3;
		n3.next = n4;
		n4.next = X;
		X.next = Y;
		Y.next = Z;

		MyList l2 = a;
		a.next = b;
		b.next = X;

		print(l1);
		print(l2);


		// Check if two lists intersect
		MyList t1 = l1;
		int len1 = 1;
		while (t1.next != null) {
			t1 = t1.next;
			len1++;
		}

		MyList t2 = l2;
		int len2 = 1;
		while (t2.next != null) {
			t2 = t2.next;
			len2++;
		}

		if (t1 != t2) {
			System.out.println("List dont intersect");
			return;
		}

		MyList h1 = l1;
		MyList h2 = l2;
		if (len1 > len2) {
			for (int i = 0; i < (len1 - len2); i++) {
				h1 = h1.next;
			}
		} else if (len2 > len1) {
			for (int i = 0; i < (len2 - len1); i++) {
				h2 = h2.next;
			}
		}

		print(h1);
		print(h2);

		while (h1 != null && h2 != null) {
			if (h1 == h2) {
				System.out.println(h1.data);
				return;
			}
			h1 = h1.next;
			h2 = h2.next;
		}


		// Connect the second list to the tail of the first one
		/*t1.next = l2;

		// Use two runners to get the intersection
		MyList runner = l1;
		MyList fastRunner = l2;
		while (runner != null) {
			if (runner.next.data == fastRunner.next.data) {
				System.out.println(runner.next.data);
				return;
			}
			runner = runner.next;
			fastRunner = fastRunner.next.next;
		}*/
		System.out.println("Failure");
	}
}
