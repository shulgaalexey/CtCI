// Sort Stack: Write a program to sort a stack such that the smallest items are on the top. You can use
// an additional temporary stack, but you may not copy the elements into any other data structure
// (such as an array). The stack supports the following operations: push, pop, peek, and is Empty.
import java.util.*;

public class Task_3_5 {
	static class MyStack {
		private final int capacity = 16;
		private final int[] buffer = new int[capacity];
		private int idx = -1;
		void push(int n) {
			if ((idx + 1) == capacity) {
				throw new ArrayIndexOutOfBoundsException("Stack overflow");
			}
			idx++;
			buffer[idx] = n;
		}
		int pop() {
			if (isEmpty()) {
				throw new ArrayIndexOutOfBoundsException("Stack is empty");
			}
			int tmp = buffer[idx];
			idx--;
			return tmp;
		}
		int peek() {
			if (isEmpty()) {
				throw new ArrayIndexOutOfBoundsException("Stack is empty");
			}
			return buffer[idx];
		}
		boolean isEmpty() {
			return idx == -1;
		}
		void dbgTrace() {
			System.out.println("--------------");
			if (idx == -1) {
				System.out.println("empty");
				return;
			}
			for (int i = 0; i < buffer.length; i++) {
				System.out.print(buffer[i] + " ");
			}
			System.out.println();
			System.out.println("idx: " + idx);
		}
	}

	static boolean cmp(int a, int b, boolean desc) {
		if (desc) {
			return a >= b;
		} else {
			return a < b;
		}
	}

	static void sort(MyStack s1, MyStack s2, boolean desc) {
		MyStack left = s1;
		MyStack right = s2;
		boolean op = desc;

		boolean repeat = true;
		while (repeat) {
			repeat = false;
			boolean swapped = false;
			while (!left.isEmpty()) {
				int tmp = left.pop();
				if (!swapped && !left.isEmpty() && cmp(tmp, left.peek(), op)) {
					repeat = true;
					swapped = true;
					right.push(left.pop());
				}
				right.push(tmp);
			}

			MyStack stmp = left;
			left = right;
			right = stmp;
			op = !op;
		}
		if (op != desc) {
			while (!right.isEmpty()) {
				left.push(right.pop());
			}
		}
	}

	static void sortBook(MyStack s, MyStack buf) {
		while (!s.isEmpty()) {
			int tmp = s.pop();
			while (!buf.isEmpty() && buf.peek() > tmp) {
				s.push(buf.pop());
			}
			buf.push(tmp);
		}
		while (!buf.isEmpty()) {
			s.push(buf.pop());
		}
	}

	public static void main(String args[]) {
		MyStack s = new MyStack();
		MyStack buf = new MyStack();

		// 3 1 2 8 5 2
		s.push(5);
		s.push(8);
		s.push(2);
		s.push(1);
		s.push(3);
		s.push(2);

		s.dbgTrace();

		//sort(s, buf, true);
		sortBook(s, buf);

		System.out.println("Pop results:");
		while (!s.isEmpty()) {
			System.out.print(s.pop() + " ");
		}
		System.out.println();
	}
}
