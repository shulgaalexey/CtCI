// 3.5 Implement a MyQueue class which implements a queue using two stacks.
import java.util.*;

public class Task_3_5 {
	static class MyQueue {

		enum OP {UNKNOWN, HEAD, TAIL};
		OP lastOp = OP.UNKNOWN;

		// Used when enqueue or get back
		Stack<Integer> tail = new Stack<>();

		// Used when dequeue or get front
		Stack<Integer> head = new Stack<>();

		public MyQueue() {
		}

		public Integer front() {
			if (lastOp == OP.UNKNOWN) {
				throw new IllegalStateException("No front available");
			}
			if (lastOp == OP.TAIL) {
				copy(tail, head);
			}
			lastOp = OP.HEAD;
			return head.peek();
		}

		public Integer back() {
			if (lastOp == OP.UNKNOWN) {
				throw new IllegalStateException("No back available");
			}
			if (lastOp == OP.HEAD) {
				copy(head, tail);
			}
			lastOp = OP.TAIL;
			return tail.peek();
		}

		public void enqueue(Integer n) {
			if (lastOp == OP.HEAD) {
				copy(head, tail);
			}
			tail.push(n);
			lastOp = OP.TAIL;
		}

		public Integer dequeue() {
			if (lastOp == OP.UNKNOWN) {
				throw new IllegalStateException("Nothing to dequeue");
			}
			if (lastOp == OP.TAIL) {
				copy(tail, head);
			}
			lastOp = OP.HEAD;
			return head.pop();
		}

		static void copy(Stack<Integer> src, Stack<Integer> dst) {
			while (!dst.empty()) {
				dst.pop();
			}
			Stack<Integer> tmp = new Stack<>();
			while (!src.empty()) {
				dst.push(src.peek());
				tmp.push(src.peek());
				src.pop();
			}
			while (!tmp.empty()) {
				src.push(tmp.pop());
			}
		}

		public void dbgPrint() {
			//System.out.println("head: " + head.toString());
			//System.out.println("tail: " + tail.toString());
		}
	}

	//
	// enqueue: 1 2 3
	//   s1: 3 2 1
	//   s2: empty
	// front: must be 1
	//   s2: 1 2 3 so front is s2.peek()
	// back: must be 3
	//   s1: 3 2 1 so back is s1.peek()
	// dequeue: must be 1
	//   return s2.pop
	// enqueue: 4
	//   s1: 4
	//   s2: 2 3
	//

	public static void main(String args[]) {
		MyQueue q = new MyQueue();

		System.out.println("enque: 1 2 3");
		q.enqueue(1);
		q.enqueue(2);
		q.enqueue(3);

		q.dbgPrint();
		System.out.println("front: 1");
		System.out.println(q.front() == 1);
		q.dbgPrint();
		System.out.println("back: 3");
		System.out.println(q.back() == 3);
		q.dbgPrint();
		System.out.println("dequeue: 1");
		System.out.println(q.dequeue() == 1);
		q.dbgPrint();
		System.out.println("back: 3");
		System.out.println(q.back() == 3);
		q.dbgPrint();
		System.out.println("front: 2");
		System.out.println(q.front() == 2);
		q.dbgPrint();
		System.out.println("enque: 4");
		q.enqueue(4);
		q.dbgPrint();
		System.out.println("back: 4");
		System.out.println(q.back() == 4);
		q.dbgPrint();
		System.out.println("front: 2");
		System.out.println(q.front() == 2);
	}
}
