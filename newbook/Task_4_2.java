// Minimal Tree: Given a sorted (increasing order) array with unique integer elements, write an
// algorithm to create a binary search tree with minimal height.
import java.util.*;

public class Task_4_2 {
	static class MyTree {
		int data;
		MyTree left;
		MyTree right;
		MyTree(int data) {
			this.data = data;
		}
	}

	static MyTree convertArrayToTree(int arr[], int startIdx, int finishIdx) {
		if (startIdx > finishIdx) {
			return null;
		}
		int mid = (startIdx + finishIdx) / 2;
		MyTree t = new MyTree(arr[mid]);
		t.left = convertArrayToTree(arr, startIdx, mid - 1);
		t.right = convertArrayToTree(arr, mid + 1, finishIdx);
		return t;
	}

	static MyTree arrayToTree(int arr[]) {
		return convertArrayToTree(arr, 0, arr.length - 1);
	}

	static List<List<Integer>> screen;

	static void print(MyTree t, int level) {
		if (t == null) {
			return;
		}
		if (screen.size() <= level) {
			screen.add(new ArrayList<Integer>());
		}
		screen.get(level).add(t.data);
		print(t.left, level + 1);
		print(t.right, level + 1);
	}

	public static void main(String args[]) {
		//int arr[] = {1};
		//int arr[] = {1, 2};
		//int arr[] = {1, 2, 3};
		//int arr[] = {1, 2, 3, 4};
		//int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
		//int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

		MyTree t = arrayToTree(arr);

		screen = new ArrayList<List<Integer>>();
		print(t, 0);
		System.out.println(screen);
	}
}
