// Stack of Plates: Imagine a (literal) stack of plates. If the stack gets too high, it might topple.
// Therefore, in real life, we would likely start a new stack when the previous stack exceeds some
// threshold. Implement a data structure SetOfStacks that mimics this. SetO-fStacks should be
// composed of several stacks and should create a new stack once the previous one exceeds capacity.
// SetOfStacks. push() and SetOfStacks. pop() should behave identically to a single stack
// (that is, pop () should return the same values as it would if there were just a single stack).
// FOLLOW UP
// Implement a function popAt ( int index) which performs a pop operation on a specific sub-stack.
import java.util.*;

public class Task_3_3 {
	static class MyStack {
		private int limit;
		private List<Stack<Integer>> stacks = new ArrayList<>();
		private int curStack = 0;
		MyStack(int limit) {
			this.limit = limit;
			stacks.add(new Stack<>());
		}
		void push(int n) {
			if (stacks.get(curStack).size() == limit) {
				if (stacks.size() <= (curStack + 1)) {
					stacks.add(new Stack<>());
				}
				curStack++;
				stacks.get(curStack).push(n);
			} else {
				stacks.get(curStack).push(n);
			}
		}
		int pop() {
			int tmp = stacks.get(curStack).pop();
			if (stacks.get(curStack).isEmpty()) {
				stacks.remove(curStack);
				curStack--;
			}
			return tmp;
		}
		int popAt(int idx) {
			curStack = idx;
			int tmp = pop();
			Stack<Integer> buf = new Stack<>();
			for (int i = stacks.size() - 1; i > idx; i--) {
				while (!stacks.get(i).isEmpty()) {
					buf.push(stacks.get(i).pop());
				}
				stacks.remove(i);
			}
			while (!buf.isEmpty()) {
				push(buf.pop());
			}
			return tmp;
		}
		void dbgTrace() {
			System.out.println("--------------------");
			for (Stack<Integer> s: stacks) {
				System.out.println(s);
			}
		}
	}

	public static void main(String arg[]) {
		MyStack s = new MyStack(5);

		for (int i = 0; i < 17; i++) {
			s.push(i);
		}

		s.dbgTrace();

		System.out.println(s.popAt(1) == 9);

		s.dbgTrace();

		for (int i = 0; i < 16; i++) {
			System.out.println(s.pop());
		}

		s.dbgTrace();
	}
}
