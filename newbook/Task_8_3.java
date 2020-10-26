// Magic Index: A magic index in an array A [ 0...n -1] is defined to be an index such that A[ i] =
// i. Given a sorted array of distinct integers, write a method to find a magic index, if one exists, in
// array A.
// FOLLOW UP
// What if the values are not distinct?
import java.util.*;

public class Task_8_3 {
	static int magicIdx = -1;
	static boolean findMagicIndex(int[] arr, int start, int stop) {
		if (start > stop) {
			return false;
		}

		int mid = (start + stop) / 2;
		if (mid == arr[mid]) {
			magicIdx = mid;
			return true;
		}

		int stopLeft = mid - 1;
		while (stopLeft >= start) {
			if ((stopLeft - 1) >= 0 && arr[stopLeft - 1] == arr[stopLeft]) {
				stopLeft--;
				if (stopLeft == arr[stopLeft]) {
					magicIdx = stopLeft;
					return true;
				}
			} else {
				break;
			}
		}

		if (start >= arr[start] && stopLeft <= arr[stopLeft]) {
			if (findMagicIndex(arr, start, stopLeft)) {
				return true;
			}
		}

		int startRight = mid + 1;
		while (startRight <= stop) {
			if ((startRight + 1) <= stop && arr[startRight + 1] == arr[startRight]) {
				startRight++;
				if (startRight == arr[startRight]) {
					magicIdx = startRight;
					return true;
				}
			} else {
				break;
			}
		}
		if (startRight >= arr[startRight] && stop <= arr[stop]) {
			return findMagicIndex(arr, startRight, stop);
		}

		return false;
	}

	public static void main(String args[]) {
		int[] a1 = {-1, 0, 1, 2, 3, 4, 5, 7, 11, 13};
		findMagicIndex(a1, 0, a1.length - 1);
		System.out.println(magicIdx == 7);

		int[] a2 = {-1, 0, 2, 2, 2, 2, 7, 8, 9, 10};
		findMagicIndex(a2, 0, a2.length - 1);
		System.out.println(magicIdx == 2);
	}
}
