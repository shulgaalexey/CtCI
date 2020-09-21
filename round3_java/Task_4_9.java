// Interesting one
//
// 4.9 You are gven a binary tree in which each node contains a value.
// Design an algorithm to print all paths which sum to a given value.
// The path does not need to start or end at the root or a leaf, but it must go in a straight line down.
import java.util.*;

public class Task_4_9 {
	static class Tree {
		Integer data;
		Tree left;
		Tree right;
		Tree(Integer data) {
			this.data = data;
		}
	}

	static void printOnePath(List<Integer> buf, Integer from, Integer to) {
		System.out.print("path: ");
		for (int i = from; i <= to; i++) {
			System.out.print(buf.get(i) + " ");
		}
		System.out.println("");
	}

	static void doPrintPaths(Tree t, List<Integer> buf, Integer depth, Integer target) {
		if (t == null) {
			return;
		}
		if (buf.size() <= depth) {
			buf.add(0);
		}
		buf.set(depth, t.data);
		Integer cur = 0;
		for (int i = depth; i >= 0; i--) {
			cur += buf.get(i);
			if (cur == target) {
				printOnePath(buf, i, depth);
			}
		}
		doPrintPaths(t.left, buf, depth + 1, target);
		doPrintPaths(t.right, buf, depth + 1, target);
	}

	static void printPaths(Tree t, Integer target) {
		List<Integer> buf = new ArrayList<>();
		if (t.data == target) {
			printOnePath(buf, 0, 0);
		}
		buf.add(t.data);
		doPrintPaths(t.left, buf, 1, target);
		doPrintPaths(t.right, buf, 1, target);

	}

	////////////////////////////////////////////
	//
	//                     3
	//           2                    8
	//     2         4          0         9
	//  6    3    1    -2    5    -4    7    6
	//
	////////////////////////////////////////////
	//
	// target = 7
	//
	public static void main(String args[]) {
		Tree t = new Tree(3);

		t.left = new Tree(2);
		t.left.left = new Tree(2);
		t.left.left.left = new Tree(6);
		t.left.left.right = new Tree(3);
		t.left.right = new Tree(4);
		t.left.right.left = new Tree(1);
		t.left.right.right = new Tree(-2);

		t.right = new Tree(8);
		t.right.right = new Tree(9);
		t.right.right.right = new Tree(6);
		t.right.right.left = new Tree(7);
		t.right.left = new Tree(0);
		t.right.left.left = new Tree(5);
		t.right.left.right = new Tree(-4);

		printPaths(t, 7);
	}
}
