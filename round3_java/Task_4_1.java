// 4.1 Implement a function to check if a binary tree is balbnced. For the purpose of this
// question, a balanced tree is defined to be a tree such that the heights of the two
// subtrees of any node never differ by more than one.
import java.util.*;

public class Task_4_1 {
	static class Tree {
		char data;
		Tree left;
		Tree right;
		public Tree(char data) {
			this.data = data;
		}
	}

	static int getDepth(Tree root) {
		if (root == null) {
			return 1;
		}
		int depthLeft = getDepth(root.left) + 1;
		int depthRight = getDepth(root.right) + 1;
		return (depthLeft > depthRight) ? depthLeft : depthRight;
	}

	static boolean isBalanced(Tree root) {
		if (root == null) {
			return false;
		}
		int depthLeft = getDepth(root.left);
		int depthRight = getDepth(root.right);
		int dif = depthLeft - depthRight;
		return (dif <= 1 && dif >= -1);
	}

	static class Context {
		int height = 0;
		boolean isBalanced = true;
	}

	static void checkIfBalanced(Tree root, Context ctx) {
		Context ctxLeft = new Context();
		if (root.left != null) {
			ctxLeft.height = ctx.height + 1;
			checkIfBalanced(root.left, ctxLeft);
			if (!ctxLeft.isBalanced) {
				ctx.isBalanced = false;
				return;	// Backtracking, shortcutting
			}
		}

		Context ctxRight = new Context();
		if (root.right != null) {
			ctxRight.height = ctx.height + 1;
			checkIfBalanced(root.right, ctxRight);
			if (!ctxRight.isBalanced) {
				ctx.isBalanced = false;
				return;	// Backtracking, shortcutting
			}
		}

		int dif = ctxLeft.height - ctxRight.height;
		ctx.isBalanced = (dif >= -1 && dif <= 1);
	}

	static boolean isBalancedOptimal(Tree root) {
		Context ctx = new Context();
		checkIfBalanced(root, ctx);
		return ctx.isBalanced;
	}

	static public void main(String args[]) {

		/*
		 * Balanced:
		 *
		 *   A
		 *  / \
		 * B   C
		 *      \
		 *       D
		 *
		 */
		Tree tree1 = new Tree('A');
		tree1.left = new Tree('B');
		tree1.right = new Tree('C');
		tree1.right.right = new Tree('D');
		System.out.println(isBalanced(tree1) == true);


		/*
		 * Not balanced:
		 *
		 *   A
		 *  / \
		 * B   C
		 *      \
		 *       D
		 *      /
		 *     E
		 */
		Tree tree2 = new Tree('A');
		tree2.left = new Tree('B');
		tree2.right = new Tree('C');
		tree2.right.right = new Tree('D');
		tree2.right.right.left = new Tree('E');
		System.out.println(isBalanced(tree2) == false);
	}
}
