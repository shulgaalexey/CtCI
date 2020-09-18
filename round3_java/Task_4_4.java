// 4.4 Give a binary tree, design an algorithm which creates a linked list of all
// the nodes at each depth (e.g./ if yu have a tree with depth D,  you'll have D linked lists).
import java.util.*;

public class Task_4_4 {

	static class MyList {
		char data;
		MyList next;
		MyList(char data) {
			this.data = data;
		}
	}

	static class MyTree {
		char data;
		MyTree left;
		MyTree right;
		MyTree(char data) {
			this.data = data;
		}
	}

	static ArrayList<MyList> lists = new ArrayList<>();

	static void toLists(MyTree t) {
		performToList(t, 0);
	}

	static void performToList(MyTree t, int depth) {
		if (t == null)
			return;

		if (lists.size() <= depth) {
			lists.add(new MyList(t.data));
		} else {
			MyList l = lists.get(depth);
			while (l.next != null) {
				l = l.next;
			}
			l.next = new MyList(t.data);
		}
		performToList(t.left, depth + 1);
		performToList(t.right, depth + 1);
	}


	public static void main(String args[]) {
		/*
		 *      A
		 *     / \
		 *    B   C
		 *   / \   \
		 *  D   E   F
		 *
		 */

		MyTree t = new MyTree('A');
		t.left = new MyTree('B');
		t.left.left = new MyTree('D');
		t.left.right = new MyTree('E');
		t.right = new MyTree('C');
		t.right.right = new MyTree('F');

		toLists(t);

		for (MyList l: lists) {
			while (l != null) {
				System.out.print(l.data + " ");
				l = l.next;
			}
			System.out.println();
		}
	}
}
