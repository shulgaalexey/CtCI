// Towers of Hanoi: In the classic problem of the Towers of Hanoi, you have 3 towers and N disks of
// different sizes which can slide onto any tower. The puzzle starts with disks sorted in ascending order
// of size from top to bottom (i.e., each disk sits on top of an even larger one). You have the following
// constraints:
// (1) Only one disk can be moved at a time.
// (2) A disk is slid off the top of one tower onto another tower.
// (3) A disk cannot be placed on top of a smaller disk.
// Write a program to move the disks from the first tower to the last using stacks.
import java.util.*;

public class Task_8_6 {
	static class MyStack {
		private int[] buffer = new int[10];
		private int idx = -1;
		void push(int n) {
			idx++;
			buffer[idx] = n;
			dbgCheck();
		}
		int pop() {
			int tmp = buffer[idx];
			idx--;
			return tmp;
		}
		@Override
		public String toString() {
			StringBuilder sb = new StringBuilder();
			sb.append('[');
			for (int i = 0; i <= idx; i++) {
				sb.append("" + buffer[i] + ' ');
			}
			sb.append(']');
			return sb.toString();
		}
		int size() {
			return idx + 1;
		}
		private void dbgCheck() {
			for (int i = 0; i < idx; i++) {
				if (buffer[i] < buffer[i + 1]) {
					throw new IllegalStateException("Wrong item in the stack: " + buffer[i]);
				}
			}
		}
	}

	static void rebase(MyStack from, MyStack to, MyStack buf, int size) {
		if (size == 1) {
			to.push(from.pop());
		} else if (size == 2) {
			buf.push(from.pop());
			to.push(from.pop());
			to.push(buf.pop());
		} else {
			rebase(from, buf, to, size - 1);
			to.push(from.pop());
			rebase(buf, to, from, size - 1);
		}
	}

	public static void main(String args[]) {
		MyStack s1 = new MyStack();
		MyStack s2 = new MyStack();
		MyStack s3 = new MyStack();

		s1.push(7);
		s1.push(6);
		s1.push(5);
		s1.push(4);
		s1.push(3);
		s1.push(2);
		s1.push(1);
		System.out.println("tower: " + s1);

		rebase(s1, s2, s3, s1.size());

		System.out.println("from: " + s1);
		System.out.println("to: " + s2);
		System.out.println("buf: " + s3);
	}
}
