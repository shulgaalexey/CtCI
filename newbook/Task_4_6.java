// Successor: Write an algorithm to find the "next" node (i.e., in-order successor) of a given node in a
// binary search tree. You may assume that each node has a link to its parent.
import java.util.*;

public class Task_4_6 {
	static class MyTree {
		int data;
		MyTree left;
		MyTree right;
		MyTree parent;
		MyTree(int data) {
			this.data = data;
		}

		@Override
		public String toString() {
			return "" + data;
		}
	}

	static MyTree getNext(MyTree t, MyTree n) {
		if (t.parent == null && t.right == null) {
			return null;
		}
		if (n.right != null) {
			// If there is a right sub-tree, than we need a left-most bottom node
			MyTree pos = n.right;
			while (pos.left != null) {
				pos = pos.left;
			}
			return pos;
		} else {
			if (n == n.parent.left) {
				return n.parent;
			} else {
				MyTree pos = n;
				while (pos.parent != null && pos == pos.parent.right) {
					pos = pos.parent;
				}
				return pos.parent;
			}
		}
	}

	public static void main(String args[]) {
		// Tree
		//            5
		//        2        7
		//      1  3      6
		//          4
		MyTree n1 = new MyTree(1);
		MyTree n2 = new MyTree(2);
		MyTree n3 = new MyTree(3);
		MyTree n4 = new MyTree(4);
		MyTree n5 = new MyTree(5);
		MyTree n6 = new MyTree(6);
		MyTree n7 = new MyTree(7);

		MyTree t = n5;
		n5.left = n2;
		n5.right = n7;

		n2.left = n1;
		n2.right = n3;
		n2.parent = n5;

		n1.parent = n2;

		n3.right = n4;
		n3.parent = n2;

		n4.parent = n3;

		n7.left = n6;
		n7.parent = n5;

		n6.parent = n7;

		System.out.println(getNext(t, n1).data == 2);
		System.out.println(getNext(t, n2).data == 3);
		System.out.println(getNext(t, n3).data == 4);
		System.out.println(getNext(t, n4).data == 5);
		System.out.println(getNext(t, n5).data == 6);
		System.out.println(getNext(t, n6).data == 7);
		System.out.println(getNext(t, n7) == null);
	}
}
