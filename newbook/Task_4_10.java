// Check Subtree: T1 and T2 are two very large binary trees, with T1 much bigger than T2. Create an
// algorithm to determine if T2 is a subtree of T1.
// A tree T2 is a subtree of T1 if there exists a node n in T1 such that the subtree of n is identical to T2.
// That is, if you cut off the tree at node n, the two trees would be identical.
import java.util.*;

public class Task_4_10 {
	static class MyTree {
		char data;
		MyTree left;
		MyTree right;
		MyTree(char data) {
			this.data = data;
		}
	}

	static boolean result = false;
	static int sate = 0;	// 0 - traversing, 1 - checking, 2 - YES

	static boolean compare(MyTree t1, MyTree t2) {
		if (t1 == null && t2 == null) {
			return true;
		}
		if (t1 == null || t2 == null) {
			return false;
		}

		if (t1.data != t2.data) {
			return false;
		}

		return compare(t1.left, t2.left) && compare(t1.right, t2.right);
	}

	static boolean isSubTree(MyTree small, MyTree large) {
		if (result) {
			return true;
		}
		if (large == null) {
			return false;
		}
		if (small.data == large.data) {
			if (compare(small, large)) {
				result = true;
				return true;
			}
		} else {
			return isSubTree(small, large.left) || isSubTree(small, large.right);
		}
		return false;
	}

	public static void main(String args[]) {
		//               a
		//         b           c
		//     d      e     f     g
		//          h   i          j
		//             k
		//
		//     e
		//  h    i
		//      k

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

		MyTree t1 = a;
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


		MyTree e2 = new MyTree('e');
		MyTree h2 = new MyTree('h');
		MyTree i2 = new MyTree('i');
		MyTree k2 = new MyTree('k');

		MyTree t2 = e2;
		e2.left = h2;
		e2.right = i2;
		i2.left = k2;

		System.out.println(isSubTree(t2, t1) == true);
	}
}
