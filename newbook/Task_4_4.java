// Check Balanced: Implement a function to check if a binary tree is balanced. For the purposes of
// this question, a balanced tree is defined to be a tree such that the heights of the two subtrees of any
// node never differ by more than one.
import java.util.*;

public class Task_4_4 {
	static class MyTree {
		int data;
		MyTree left;
		MyTree right;
		MyTree(int data) {
			this.data = data;
		}
	}

	static int getHeight(MyTree t) {
		if (t == null) {
			return 0;
		}
		int left = getHeight(t.left);
		int right = getHeight(t.right);
		return Math.max(left, right) + 1;
	}


	static boolean checkBalanced(MyTree t) {
		if (terminate) {
			return false;
		}
		if (t == null) {
			return true;
		}

		if (Math.abs(getHeight(t.left) - getHeight(t.right)) > 1) {
			terminate = true;
			return false;
		}

		boolean left = checkBalanced(t.left);
		if (!left) {
			terminate = true;
		}
	    boolean right = checkBalanced(t.right);
		if (!right) {
			terminate = true;
		}
		return left && right;
	}

	static boolean terminate = false;
	static boolean isBalanced(MyTree t) {
		terminate = false;
		return checkBalanced(t);
	}

	static void memoHeights(MyTree t, Map<MyTree, Integer> heights) {
		if (t == null) {
			return;
		}
		if (heights.containsKey(t)) {
			return;
		}
		if (t.left == null && t.right == null) {
			heights.put(t, 1);
			return;
		}
		int left = 0;
		if (t.left != null) {
			memoHeights(t.left, heights);
			left = heights.get(t.left);
		}
		int right = 0;
		if (t.right != null) {
			memoHeights(t.right, heights);
			right = heights.get(t.right);
		}
		heights.put(t, Math.max(left, right) + 1);
	}

	static boolean checkBalancedWithMemo(MyTree t, Map<MyTree, Integer> heights) {
		if (terminate) {
			return false;
		}
		if (t == null) {
			return true;
		}
		if (t.left != null && t.right != null) {
			if (Math.abs(heights.get(t.left) - heights.get(t.right)) > 1) {
				terminate = true;
				return false;
			}
		} else if (t.left != null) {
			if (heights.get(t.left) > 1) {
				terminate = true;
				return false;
			}
		} else if (t.right != null) {
			if (heights.get(t.right) > 1) {
				terminate = true;
				return false;
			}
		}
		return checkBalancedWithMemo(t.left, heights)
			&& checkBalancedWithMemo(t.right, heights);

	}

	static boolean isBalancedWithMemo(MyTree t) {
		terminate = false;
		Map<MyTree, Integer> heights = new HashMap<>();
		memoHeights(t, heights);
		return checkBalancedWithMemo(t, heights);
	}

	static final int ERR = -100;
	static int checkHeight(MyTree t) {
		if (t == null) {
			return 0;
		}

		int leftHeight = checkHeight(t.left);
		if (leftHeight == ERR) {
			return ERR;
		}

		int rightHeight = checkHeight(t.right);
		if (rightHeight == ERR) {
			return ERR;
		}

		if (Math.abs(leftHeight - rightHeight) > 1) {
			return ERR;
		}
		return Math.max(leftHeight, rightHeight) + 1;
	}

	static boolean isBalancedBook(MyTree t) {
		return checkHeight(t) != ERR;
	}

	public static void main(String args[]) {
		// Not balanced tree:
		//          5
		//     2        7
		//   1  3
		//       4
		//
		// Balanced tree:
		//          5
		//     2        7
		//   1  3      6
		//       4

		MyTree t = new MyTree(5);
		t.left = new MyTree(2);
		t.left.left = new MyTree(1);
		t.left.right = new MyTree(3);
		t.left.right.right = new MyTree(4);
		t.right = new MyTree(7);
		System.out.println(isBalanced(t) == false);
		System.out.println(isBalancedWithMemo(t) == false);
		System.out.println(isBalancedBook(t) == false);

		t.right.left = new MyTree(6);
		System.out.println(isBalanced(t) == true);
		System.out.println(isBalancedWithMemo(t) == true);
		System.out.println(isBalancedBook(t) == true);
	}
}
