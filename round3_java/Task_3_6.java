// 3.6 Write a programm to sort a stack in ascending order (with biggest items on top).
// You may use at most one additional stack to hold items, but you may not copy the elements
// into any other data structure (such as an array).
// The stack supports the following operations: push, pop, peek, isEmpty
import java.util.*;

public class Task_3_6 {

	static boolean rebase(Stack<Integer> src, Stack<Integer> dst) {
		dst.push(src.pop());
		while (!src.isEmpty()) {
			if (dst.peek() <= src.peek()) {
				dst.push(src.pop());
			} else {
				Integer x = src.pop();
				while (!dst.isEmpty()) {
					src.push(dst.pop());
				}
				src.push(x);
				return true;
			}
		}
		while (!dst.isEmpty()) {
			src.push(dst.pop());
		}
		return false;
	}


	static void sort(Stack<Integer> s) {
		Stack<Integer> buf = new Stack<>();
		while (rebase(s, buf)) {
			//System.out.println(s);
		}
	}

	public static void main(String args[]) {
		Stack<Integer> s = new Stack<>();
		s.push(1);
		s.push(5);
		s.push(2);
		s.push(2);
		s.push(8);
		s.push(3);

		sort(s);

		System.out.println("Result:");
		while (!s.isEmpty()) {
			System.out.println(s.pop());
		}
	}
}
