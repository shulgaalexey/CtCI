// BST Sequences: A binary search tree was created by traversing through an array from left to right
// and inserting each element. Given a binary search tree with distinct elements, print all possible
// arrays that could have led to this tree.
// EXAMPLE
// Input:
//    2
//  1  3
//  Output: {2, 1, 3}, {1, 3, 1}

import java.util.*;

public class Task_4_9 {
	static class MyTree {
		int data;
		String state = "l";
		MyTree left;
		MyTree right;
		MyTree(int data) {
			this.data = data;
		}
		@Override
		public String toString() {
			return "" + data;
		}
	}


	static Stack<MyTree> stack = new Stack<>();
	static boolean changed = true;

	static void toStack(MyTree t) {
		if (t == null) {
			return;
		}
		stack.push(t);
		toStack(t.left);
		toStack(t.right);
	}

	static void changeState() {
		while (!stack.isEmpty()) {
			MyTree t = stack.pop();
			if (t.state == "l") {
				t.state = "r";
				changed = true;
				return;
			}
		}
		changed = false;
	}

	static void traverseState(MyTree t, List<Integer> path) {
		if (t == null) {
			return;
		}
		path.add(t.data);
		if (t.state == "l") {
			traverseState(t.left, path);
			traverseState(t.right, path);
		} else if (t.state == "r") {
			traverseState(t.right, path);
			traverseState(t.left, path);
		}
	}

	static void printSources(MyTree t) {
		toStack(t);
		do {
			changed = false;
			List<Integer> path = new ArrayList<>();
			traverseState(t, path);
			System.out.println(path);
			changeState();
			if (!changed) {
				return;
			}
		} while (changed);
	}

	// FROM BOOK ---------
	static ArrayList<LinkedList<Integer>> allSequences(MyTree t) {
		ArrayList<LinkedList<Integer>> result = new ArrayList<LinkedList<Integer>>();

		if (t == null) {
			result.add(new LinkedList<Integer>());
			return result;
		}

		LinkedList<Integer> prefix = new LinkedList<>();
		prefix.add(t.data);

		// Recurse on left and right sub-tree
		ArrayList<LinkedList<Integer>> leftSeq = allSequences(t.left);
		ArrayList<LinkedList<Integer>> rightSeq = allSequences(t.right);

		// Weave together each leaf from left and right sides
		for (LinkedList<Integer> left: leftSeq) {
			for (LinkedList<Integer> right: rightSeq) {
				ArrayList<LinkedList<Integer>> weaved = new ArrayList<LinkedList<Integer>>();
				weaveLists(left, right, weaved, prefix);
				result.addAll(weaved);
			}
		}
		return result;
	}

	static void weaveLists(LinkedList<Integer> first, LinkedList<Integer> second,
			ArrayList<LinkedList<Integer>> results, LinkedList<Integer> prefix) {
		if (first.isEmpty() || second.isEmpty()) {
			LinkedList<Integer> result = (LinkedList<Integer>) prefix.clone();
			result.addAll(first);
			result.addAll(second);
			results.add(result);
			return;
		}

		int headFirst = first.removeFirst();
		prefix.addLast(headFirst);
		weaveLists(first, second, results, prefix);
		prefix.removeLast();
		first.addFirst(headFirst);

		int headSecond = second.removeFirst();
		prefix.addLast(headSecond);
		weaveLists(first, second, results, prefix);
		prefix.removeLast();
		second.addFirst(headSecond);
	}
	// ------------------

	public static void main(String args[]) {
		// Input:
		//    2
		//  1  3
		//  Levels:
		//  2
		//  1, 3
		//  Output: {2, 1, 3}, {1, 3, 1}
		//
		// Input:
		//       4
		//   2      6
		//  1 3    5
		//
		//  Levels:
		//  4
		//  2, 6
		//  1, 3, 5
		//  Output: {4, 2, 6, 1, 3, 5}, {4, 6, 2, 3, 1, 5}, ...

		// Solution
		// 1. Split on levels
		// 2. Print for each level
		//   k-th permutation of the level

		MyTree n1 = new MyTree(1);
		MyTree n2 = new MyTree(2);
		MyTree n3 = new MyTree(3);
		MyTree n4 = new MyTree(4);
		MyTree n5 = new MyTree(5);
		MyTree n6 = new MyTree(6);

		MyTree t = n2;
		n2.left = n1;
		n2.right = n3;

		printSources(t);
		System.out.println("Book's method: " + allSequences(t));

		t = n4;
		n4.left = n2;
		n4.right = n6;
		n2.left = n1;
		n2.right = n3;
		n6.left = n5;
		printSources(t);
		System.out.println("Book's method: " + allSequences(t));
	}
}
