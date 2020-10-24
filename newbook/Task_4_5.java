// Validate BST: Implement a function to check if a binary tree is a binary search tree.
import java.util.*;

public class Task_4_5 {
	static class MyTree {
		int data;
		MyTree left;
		MyTree right;
		MyTree(int data) {
			this.data = data;
		}
	}

	static final int INT_MIN = -100;
	static final int INT_MAX = 100;

	static boolean checkBst(MyTree t, int from, int to) {
		if (t == null) {
			return true;
		}

		if (t.data <= from || t.data > to) {
			return false;
		}

		return checkBst(t.left, from, t.data)
			&& checkBst(t.right, t.data, to);
	}

	static boolean isBst(MyTree t) {
		return checkBst(t, INT_MIN, INT_MAX);
	}

	public static void main(String args[]) {
		// Search BST:
		//        5
		//   2        7
		// 1  3      6
		//     4
		//
		// Not search BST:
		//        5
		//   2        7
		// 1  3      3 <----
		//     4

		MyTree t = new MyTree(5);
		t.left = new MyTree(2);
		t.left.left = new MyTree(1);
		t.left.right = new MyTree(3);
		t.left.right.right = new MyTree(4);
		t.right = new MyTree(7);
		t.right.left = new MyTree(6);

		System.out.println(isBst(t) == true);

		t.right.left = new MyTree(3);
		System.out.println(isBst(t) == false);
	}
}
