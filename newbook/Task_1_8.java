// Zero Matrix: Write an algorithm such that if an element in an MxN matrix is 0, its entire row and
// column are set to 0.
import java.util.*;

public class Task_1_8 {
	static void print(int[][] M) {
		System.out.println();
		for (int i = 0; i < M.length; i++) {
			for (int j = 0; j < M[i].length; j++) {
				System.out.print(M[i][j] + " ");
			}
			System.out.println();
		}
	}

	public static void main(String args[]) {
		int [][] M = {
			{1, 2, 3, 4, 5},
			{1, 2, 3, 0, 5},
			{1, 2, 3, 4, 5},
			{1, 2, 0, 4, 5},
			{1, 2, 3, 4, 4},
			{1, 2, 3, 4, 4},
			{1, 2, 3, 4, 4},
			{1, 2, 3, 4, 5},
		};

		print(M);

		boolean zeroTopRow = false;
		for (int j = 0; j < M[0].length; j++) {
			if (M[0][j] == 0) {
				zeroTopRow = true;
				break;
			}
		}
		boolean zeroLeftCol = false;
		for (int i = 0; i < M.length; i++) {
			if (M[i][0] == 0) {
				zeroLeftCol = true;
				break;
			}
		}


		for (int i = 0; i < M.length; i++) {
			for (int j = 0; j < M[i].length; j++) {
				if (M[i][j] == 0) {
					M[0][j] = 0;
					M[i][0] = 0;
				}
			}
		}


		for (int j = 1; j < M[0].length; j++) {
			if (M[0][j] == 0) {
				for (int i = 1; i < M.length; i++) {
					M[i][j] = 0;
				}
			}
		}

		for (int i = 1; i < M.length; i++) {
			if (M[i][0] == 0) {
				for (int j = 1; j < M[i].length; j++) {
					M[i][j] = 0;
				}
			}
		}

		if (zeroLeftCol) {
			for (int i = 0; i < M.length; i++) {
				M[i][0] = 0;
			}
		}

		if (zeroTopRow) {
			for (int j = 0; j < M[0].length; j++) {
				M[0][j] = 0;
			}
		}

		print(M);
	}
}
