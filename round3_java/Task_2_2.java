// 2.2 Implement an algorithm to find the kth to the last element of a singly linked list
import java.util.*;

public class Task_2_2 {

	static class List {
		char val;
		List next;
		List(char val) {
			this.val = val;
			this.next = next;
		}
	}

	public static void main(String args[]) {
		List l = new List('a');
		l.next = new List('b');
		l.next.next = new List('c');
		l.next.next.next = new List('d');
		l.next.next.next.next = new List('e');
		l.next.next.next.next.next = new List('f');

		int k = 2;

		List ptrK = l;
		while (k --> 0 && ptrK != null) {
			ptrK = ptrK.next;
		}

		List ptr = l;
		while (ptrK != null) {
			ptr = ptr.next;
			ptrK = ptrK.next;
		}

		System.out.println(ptr.val);
	}
}
