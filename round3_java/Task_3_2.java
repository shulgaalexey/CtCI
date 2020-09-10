// 3.2 How would you design a stack which,
// in addition to push and pop, also has a function min which returns the minimum element?
// Push, pop and min should all operate in O(1) time.
import java.util.*;

public class Task_3_2 {

	static class List {
		int val;
		List next;
		public List(int val) {
			this.val = val;
		}
		public List(int val, List next) {
			this.val = val;
			this.next = next;
		}
	}


	static class MinStack {
		static List vals;
		static List mins;

		public MinStack() {
		}

		void push(Integer v) {
			if (vals == null) {
				vals = new List(v);
			} else {
				vals = new List(v, vals);
			}

			if (mins == null) {
				mins = new List(v);
			} else {
				if (v <= mins.val) {
					mins = new List(v, mins);
				}
			}
		}

		int pop() {
			int v = vals.val;
			vals = vals.next;
			if (v == mins.val) {
				mins = mins.next;
			}
			return v;

		}

		int min() {
			return mins.val;
		}
	};

	public static void main(String args[]) {
		MinStack ms = new MinStack();
		ms.push(1);
		System.out.println(ms.min() == 1);
		ms.push(1);
		System.out.println(ms.min() == 1);
		System.out.println(ms.pop() == 1);
		System.out.println(ms.min() == 1);
		System.out.println(ms.pop() == 1);
		ms.push(5);
		ms.push(3);
		ms.push(7);
		System.out.println(ms.min() == 3);
	}
}
