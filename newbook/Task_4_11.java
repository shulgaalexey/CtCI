// Random Node: You are implementing a binary tree class from scratch which, in addition to
// insert, find, and delete, has a method getRandomNode() which returns a random node
// from the tree. All nodes should be equally likely to be chosen. Design and implement an algorithm
// for getRandomNode, and explain how you would implement the rest of the methods.
import java.util.*;

public class Task_4_11 {
	static class MyTree {
		char data;
		MyTree left;
		MyTree right;
		MyTree(char data) {
			this.data = data;
		}
		@Override
		public String toString() {
			return "" + data;
		}
	}

	static int getSize(MyTree t) {
		if (t == null) {
			return 0;
		}
		int size = 1;
		if (t.left != null) {
			size += getSize(t.left);
		}
		if (t.right != null) {
			size += getSize(t.right);
		}
		return size;
	}

	static int cur = -1;
	static MyTree traverseUntil(MyTree t, final int target) {
		if (t == null) {
			return null;
		}
		cur++;
		if (cur == target) {
			return t;
		}

		MyTree left = traverseUntil(t.left, target);
		if (left != null) {
			return left;
		}
		MyTree right = traverseUntil(t.right, target);
		return right;
	}

	static Random rand = new Random();

	static MyTree getRandomNode(MyTree t) {
		int size = getSize(t);
		int target = rand.nextInt(size);
		cur = -1;
		return traverseUntil(t, target);
	}


	public static void main(String args[]) {
		MyTree a = new MyTree('a');
		MyTree b = new MyTree('b');
		MyTree c = new MyTree('c');
		MyTree d = new MyTree('d');
		MyTree e = new MyTree('e');
		MyTree f = new MyTree('f');
		MyTree g = new MyTree('g');
		MyTree h = new MyTree('h');
		MyTree i = new MyTree('i');
		MyTree j = new MyTree('j');
		MyTree k = new MyTree('k');

		a.left = b;
		a.right = c;
		b.left = d;
		b.right = e;
		e.left = h;
		e.right = i;
		i.left = k;
		c.left = f;
		c.right = g;
		g.right = j;

		MyTree t = a;

		Map<Character, Integer> stats = new HashMap<>();
		stats.put('a', 0);
		stats.put('b', 0);
		stats.put('c', 0);
		stats.put('d', 0);
		stats.put('e', 0);
		stats.put('f', 0);
		stats.put('g', 0);
		stats.put('h', 0);
		stats.put('i', 0);
		stats.put('j', 0);
		stats.put('k', 0);
		for (int idx = 0; idx < 2200; idx++) {
			MyTree n = getRandomNode(t);
			if (n == null) {
				System.out.println("null");
			} else {
				stats.put(n.data, stats.get(n.data) + 1);
			}
		}
		System.out.println(stats);
	}
}
