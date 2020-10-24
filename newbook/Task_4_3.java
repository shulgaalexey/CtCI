// List of Depths: Given a binary tree, design an algorithm which creates a linked list of all the nodes
// at each depth (e.g., if you have a tree with depth D, you'll have D linked lists).
import java.util.*;

public class Task_4_3 {
	static class MyTree {
		Integer data;
		MyTree left;
		MyTree right;
		MyTree(Integer data) {
			this.data = data;
		}
		@Override
		public String toString() {
			return "" + data;
		}
	}

	static void convertTreeToLists(MyTree t,
			List<LinkedList<Integer>> lists, int level) {
		if (t == null) {
			return;
		}
		if (lists.size() <= level) {
			lists.add(new LinkedList<Integer>());
		}
		lists.get(level).add(t.data);
		convertTreeToLists(t.left, lists, level + 1);
		convertTreeToLists(t.right, lists, level + 1);
	}

	static List<LinkedList<Integer>> treeToLists(MyTree t) {
		List<LinkedList<Integer>> lists = new ArrayList<LinkedList<Integer>>();
		convertTreeToLists(t, lists, 0);
		return lists;
	}

	static List<LinkedList<MyTree>> treeToListsBfs(MyTree t) {
		List<LinkedList<MyTree>> result = new ArrayList<LinkedList<MyTree>>();
		LinkedList<MyTree> current = new LinkedList<>();
		current.add(t);
		while (!current.isEmpty()) {
			result.add(current);
			LinkedList<MyTree> parents = current;
			current = new LinkedList<>();
			for (MyTree p: parents) {
				if (p.left != null) {
					current.add(p.left);
				}
				if (p.right != null) {
					current.add(p.right);
				}
			}
		}
		return result;
	}

	public static void main(String args[]) {
		// Tree:
		//        5
		//    2      7
		//  1  3    6
		//      4
		//
		// Result:
		//  5
		//  2 7
		//  1 3 6
		//  4
		MyTree t = new MyTree(5);
		t.left = new MyTree(2);
		t.left.left = new MyTree(1);
		t.left.right = new MyTree(3);
		t.left.right.right = new MyTree(4);
		t.right = new MyTree(7);
		t.right.left = new MyTree(6);

		System.out.println(treeToLists(t));
	}
}
