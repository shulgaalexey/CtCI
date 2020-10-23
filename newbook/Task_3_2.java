// Stack Min: How would you design a stack which, in addition to push and pop, has a function min
// which returns the minimum element? Push, pop and min should all operate in 0(1) time.
import java.util.*;

public class Task_3_2 {

	static class MyStack {
		private Stack<Integer> data = new Stack<>();
		private Stack<Integer> mins = new Stack<>();

		public void push(int n) {
			data.push(n);
			if (mins.isEmpty()) {
				mins.push(n);
			} else {
				if (mins.peek() >= n) {
					mins.push(n);
				}
			}
		}

		public int pop() {
			int tmp = data.pop();
			if (mins.peek() == tmp) {
				mins.pop();
			}
			return tmp;
		}

		public int min() {
			return mins.peek();
		}
	}

	public static void main(String args[]) {
		MyStack s = new MyStack();

		s.push(3);
		System.out.println(s.min() == 3);
		s.push(9);
		System.out.println(s.min() == 3);
		s.push(3);
		System.out.println(s.min() == 3);
		s.push(2);
		System.out.println(s.min() == 2);

		System.out.println(s.pop() == 2);
		System.out.println(s.min() == 3);
		System.out.println(s.pop() == 3);
		System.out.println(s.min() == 3);
	}
}
