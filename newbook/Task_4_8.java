// First Common Ancestor: Design an algorithm and write code to find the first common ancestor
// of two nodes in a binary tree. Avoid storing additional nodes in a data structure. NOTE: This is not
// necessarily a binary search tree.
import java.util.*;

public class Task_4_8 {
	static class MyTree {
		int data;
		MyTree left;
		MyTree right;
		MyTree(int data) {
			this.data = data;
		}
	}

	static MyTree findCommonAncestor(MyTree n1, MyTree n2, MyTree root) {
		if (root == null) {
			return null;
		}
		if (root == n1 && root == n2) {
			return root;
		}

		MyTree left = findCommonAncestor(n1, n2, root.left);
		if (left != null && left != n1 && left != n2) {
			return left;
		}

		MyTree right = findCommonAncestor(n1, n2, root.right);
		if (right != null && right != n1 && right != n2) {
			return right;
		}

		if (left != null && right != null) {
			return root;
		} else if (root == n1 || root == n2) {
			return root;
		} else {
			return left == null ? right : left;
		}
	}

	public static void main(String args[]) {
		//        1
		//    2       3
		//  4  5    6   7
		//      8      9
		//
		MyTree n1 = new MyTree(1);
		MyTree n2 = new MyTree(2);
		MyTree n3 = new MyTree(3);
		MyTree n4 = new MyTree(4);
		MyTree n5 = new MyTree(5);
		MyTree n6 = new MyTree(6);
		MyTree n7 = new MyTree(7);
		MyTree n8 = new MyTree(8);
		MyTree n9 = new MyTree(9);

		n1.left = n2;
		n1.right = n3;

		n2.left = n4;
		n2.right = n5;

		n3.left = n6;
		n3.right = n7;

		n5.right = n8;

		n7.left = n9;

		System.out.println(findCommonAncestor(n4, n8, n1).data == 2);
		System.out.println(findCommonAncestor(n2, n8, n1).data == 2);
		System.out.println(findCommonAncestor(n5, n3, n1).data == 1);
		System.out.println(findCommonAncestor(n2, n3, n1).data);
	}
}
