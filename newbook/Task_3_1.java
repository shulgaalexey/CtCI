// Three in One: Describe how you could use a single array to implement three stacks.
import java.util.*;

public class Task_3_1 {
	static class MyStack {
		private final int[] buffer;
		private final int capacity;
		private int first;
		private int second;
		private int third;

		MyStack(int capacity) {
			this.capacity = capacity;
			buffer = new int[capacity];
			first = -1;
			second = capacity / 3 - 1;
			third = 2 * capacity / 3 - 1;
		}


		void push1(int n) {
			if (first == -1) {
				first++;
				buffer[first] = n;
			} else {
				first++;
				if (first >= capacity / 3) {
					throw new ArrayIndexOutOfBoundsException("Stack 1 is full");
				}
				buffer[first] = n;
			}
		}
		void push2(int n) {
			if (second == (capacity / 3 - 1)) {
				second++;
				buffer[second] = n;
			} else {
				second++;
				if (second >= 2 * capacity / 3) {
					throw new ArrayIndexOutOfBoundsException("Stack 2 is full");
				}
				buffer[second] = n;
			}
		}
		void push3(int n) {
			if (third == 2 * capacity / 3) {
				third++;
				buffer[third] = n;
			} else {
				third++;
				if (third >= capacity) {
					throw new ArrayIndexOutOfBoundsException("Stack 3 is full");
				}
				buffer[third] = n;
			}
		}
		int pop1() {
			if (first == -1) {
				throw new ArrayIndexOutOfBoundsException("Stack 1 is empty");
			}
			int tmp = buffer[first];
			first--;
			return tmp;
		}
		int pop2() {
			if (second == (capacity / 3 -1)) {
				throw new ArrayIndexOutOfBoundsException("Stack 2 is empty");
			}
			int tmp = buffer[second];
			second--;
			return tmp;
		}
		int pop3() {
			if (third == (2 * capacity / 3 -1)) {
				throw new ArrayIndexOutOfBoundsException("Stack 3 is empty");
			}
			int tmp = buffer[third];
			third--;
			return tmp;
		}
		boolean isEmpty1() {
			return first == -1;
		}
		boolean isEmpty2() {
			return second == (capacity / 3 - 1);
		}
		boolean isEmpty3() {
			return third == (2 * capacity / 3 - 1);
		}

		void dbgTrace() {
			System.out.println("---------------");
			for (int i = 0; i < capacity; i++) {
				System.out.print(buffer[i] + " ");
			}
			System.out.println();
			System.out.println("first: " + first);
			System.out.println("second: " + second);
			System.out.println("third: " + third);
		}
	}

	public static void main(String[] args) {
		MyStack s = new MyStack(10);


		System.out.println(s.isEmpty1() == true);
		System.out.println(s.isEmpty2() == true);
		System.out.println(s.isEmpty3() == true);

		s.push1(1);

		s.push2(2);
		s.push2(3);

		s.push3(4);


		System.out.println(s.isEmpty1() == false);
		System.out.println(s.isEmpty2() == false);
		System.out.println(s.isEmpty3() == false);

		System.out.println(s.pop1() == 1);
		System.out.println(s.pop2() == 3);
		System.out.println(s.pop3() == 4);


		System.out.println(s.isEmpty1() == true);
		System.out.println(s.isEmpty2() == false);
		System.out.println(s.isEmpty3() == true);

		System.out.println(s.pop2() == 2);

		s.push1(1);
		s.push2(2);
		s.push3(3);
		s.push1(11);
		s.push2(22);
		s.push3(33);
		s.push1(111);
		s.push2(222);
		s.push3(333);
		s.push3(444);

		try {
			s.push1(1111);
		} catch (ArrayIndexOutOfBoundsException ae) {
			System.out.println(ae.getMessage().equals("Stack 1 is full"));
		}

		s.dbgTrace();
	}
}
