// Rotate Matrix: Given an image represented by an NxN matrix, where each pixel in the image is 4
// bytes, write a method to rotate the image by 90 degrees. Can you do this in place?
import java.util.*;

public class Task_1_6 {
	static void print(int[][] M) {
		System.out.println();
		for (int i = 0; i < M.length; i++) {
			int[] line = M[i];
			for (int j = 0; j < line.length; j++) {
				System.out.print(line[j] + " ");
			}
			System.out.println();
		}
	}

	public static void main(String args[]) {
		int[][] M = {
			{10, 11, 12, 13},
			{20, 21, 22, 23},
			{30, 31, 32, 33},
			{40, 41, 42, 43}
		};

		print(M);

		int layers = M.length / 2;
		for (int layer = 0; layer < layers; layer++) {
			int first = layer;
			int last = M.length - 1 - layer;
			for (int i = first; i < last; i++) {
				int offset = i - first;
				int top = M[first][i];

				M[first][i] = M[last - offset][first];
				M[last - offset][first] = M[last][last - offset];
				M[last][last - offset] = M[i][last];
				M[i][last] = top;
			}
		}

		print(M);
	}
}
