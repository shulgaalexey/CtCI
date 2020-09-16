// 4.3 Given a sorted (increasing order) array with nique integer elements,
// write an algorithm to create a binary search tree with minimal length.
import java.util.*;

public class Task_4_3 {

	static class Tree {
		int data;
		Tree left;
		Tree right;
		Tree(int data) {
			this.data = data;
		}
	}

	static Tree doMakeTree(int arr[], int start, int end) {
		int mid = (start + end) / 2;
		if (mid < 0 || start > end) {
			return null;
		}
		Tree root = new Tree(arr[mid]);
		root.left = doMakeTree(arr, start, mid - 1);
		root.right = doMakeTree(arr, mid + 1, end);
		return root;
	}

	static Tree tree(int arr[]) {
		return doMakeTree(arr, 0, arr.length - 1);
	}

	static ArrayList<ArrayList<Integer>> screen;
	static void doPrint(Tree tree, int depth) {
		if (tree == null) {
			return;
		}
		if (screen.size() <= depth) {
			screen.add(new ArrayList<Integer>());
		}
		ArrayList<Integer> level = screen.get(depth);
		level.add(tree.data);
		doPrint(tree.left, depth + 1);
		doPrint(tree.right, depth + 1);
	}

	static void print(Tree tree) {
		screen = new ArrayList<ArrayList<Integer>>();
		doPrint(tree, 0);
		for (ArrayList<Integer> level: screen) {
			System.out.println(level);
		}
		System.out.println("----------------");
	}

	public static void main(String args[]) {
		int arr1[] = {1};
		int arr2[] = {1, 2};
		int arr3[] = {1, 2, 3};
		int arr4[] = {1, 2, 3, 4, 5, 6, 7};
		int arr5[] = {1, 2, 3, 4, 5, 6, 7, 8};

		print(tree(arr1));
		print(tree(arr2));
		print(tree(arr3));
		print(tree(arr4));
		print(tree(arr5));
	}
}
