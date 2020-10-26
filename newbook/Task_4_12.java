// Paths with Sum: You are given a binary tree in which each node contains an integer value (which
// might be positive or negative). Design an algorithm to count the number of paths that sum to a
// given value. The path does not need to start or end at the root or a leaf, but it must go downwards
// (traveling only from parent nodes to child nodes).
import java.util.*;

public class Task_4_12 {
	static class MyTree {
		int data;
		MyTree left;
		MyTree right;
		MyTree(int data) {
			this.data = data;
		}
	}

	static int pathCnt = 0;
	static List<Integer> buffer = new ArrayList<>();

	static void countPaths(MyTree t, final int target) {
		if (t == null) {
			return;
		}

		if (t.data == target) {
			pathCnt++;
		}

		int sum = t.data;
		for (int i = buffer.size() - 1; i >= 0; i--) {
			sum += buffer.get(i);
			if (sum == target) {
				pathCnt++;
			}
		}
		buffer.add(t.data);
		countPaths(t.left, target);
		countPaths(t.right, target);
		buffer.remove(buffer.size() - 1);
	}


	public static void main(String args[]) {
		//             10
		//        5         -3
		//     3     2          11
		//   3  2     1
		MyTree t = new MyTree(10);
		t.left = new MyTree(5);
		t.left.left =  new MyTree(3);
		t.left.left.left = new MyTree(3);
		t.left.left.right = new MyTree(2);
		t.left.right = new MyTree(2);
		t.left.right.right = new MyTree(1);
		t.right = new MyTree(-3);
		t.right.right = new MyTree(11);

		countPaths(t, 8);
		System.out.println(pathCnt);
	}
}
