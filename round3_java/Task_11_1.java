// You are given two sorted arrays, A and B, where A has a large enough buffer
// at the end to hold B. Write a method to merge B into A in sorted order.
import java.util.*;

public class Task_11_1 {

	static void merge(int A[], int B[]) {
		int ptrA = A.length - B.length - 1;
		int ptrB = B.length - 1;
		int ptrIns = A.length - 1;
		while (true) {
			if (ptrA >= 0 && ptrB >= 0) {
				if (A[ptrA] > B[ptrB]) {
					A[ptrIns] = A[ptrA];
					ptrIns --;
					ptrA --;
				} else {
					A[ptrIns] = B[ptrB];
					ptrIns --;
					ptrB --;
				}
			} else if (ptrA >= 0) {
					A[ptrIns] = A[ptrA];
					ptrIns --;
					ptrA --;
			} else if (ptrB >= 0) {
					A[ptrIns] = B[ptrB];
					ptrIns --;
					ptrB --;
			} else {
				break;
			}
		}
	}

	public static void main(String args[]) {
		int A[] = {1, 3, 5, 7, 0, 0, 0};
		int B[] = {2, 4, 6};
		merge(A, B);
		for (int i = 0; i < A.length; i++) {
			System.out.println(A[i]);
		}
	}
}
