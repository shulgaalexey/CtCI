// Queue via Stacks: Implement a MyQueue class which implements a queue using two stacks.
import java.util.*;

public class Task_3_4 {
	static class MyStack {
		private final int capacity = 10;
		private final int[] buffer = new int[capacity];
		private int idx = -1;
		void push(int n) {
			if ((idx + 1) >= capacity) {
				throw new ArrayIndexOutOfBoundsException("Stack is full");
			}
			idx++;
			buffer[idx] = n;
		}
		int pop() {
			if (idx == -1) {
				throw new ArrayIndexOutOfBoundsException("Stack is empty");
			}
			int tmp = buffer[idx];
			idx--;
			return tmp;
		}
		boolean isEmpty() {
			return idx == -1;
		}
		void dbgTrace() {
			System.out.println("  _______");
			System.out.print("  ");
			for (int i = 0; i < buffer.length; i++) {
				System.out.print(buffer[i] + " ");
			}
			System.out.println();
			System.out.println("  idx: " + idx);
		}
	}

	static class MyQueue {
		private MyStack head = new MyStack();
		private MyStack tail = new MyStack();
		void offer(int n) {
			tail.push(n);
		}
		int poll() {
			if (head.isEmpty()) {
				rebaseTailToHead();
			}
			return head.pop();
		}
		boolean isEmpty() {
			return head.isEmpty() && tail.isEmpty();
		}
		private void rebaseTailToHead() {
			while (!tail.isEmpty()) {
				head.push(tail.pop());
			}
		}
		void dbgTrace() {
			System.out.println("-------------------");
			head.dbgTrace();
			tail.dbgTrace();
		}
	}

	public static void main(String args[]) {
		MyQueue q = new MyQueue();

		System.out.println(q.isEmpty() == true);
		for (int i = 1; i <= 5; i++) {
			q.offer(i);
		}
		System.out.println(q.isEmpty() == false);

		System.out.println(q.poll() == 1);
		System.out.println(q.poll() == 2);

		q.offer(6);

		while (!q.isEmpty()) {
			System.out.println(q.poll());
		}
		q.dbgTrace();
	}
}
