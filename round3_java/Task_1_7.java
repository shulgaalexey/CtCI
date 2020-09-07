// 1.7 Write an algorithm such that if an element in an MxN matrix is 0,
// its entire row and column are set to 0;
import java.util.*;

public class Task_1_7 {
	static void print(int [][] m) {
		for (int i = 0; i < m.length; i++) {
			int [] row = m[i];
			for (int j = 0; j < row.length; j++) {
				System.out.print(row[j]);
				System.out.print('\t');
			}
			System.out.println();
		}
	}

	public static void main(String args[]) {
		System.out.println("Input");
		int [][] m = {
			{1, 2, 3, 4, 5},
			{6, 7, 8, 0, 9},
			{10, 11, 12, 13, 14},
			{15, 0, 16, 17, 18},
			{19, 20, 21, 22, 23},
			{24, 25, 26, 27, 28}
		};
		print(m);

		System.out.println("Mark");
		for (int i = 0; i < m.length; i++) {
			int [] row = m[i];
			for (int j = 0; j < row.length; j++) {
				if (row[j] == 0) {
					row[0] = 0;
					m[0][j] = 0;
				}
			}
		}
		print(m);

		System.out.println("Zero column");
		for (int i = 0; i < m[0].length; i++) {
			if (m[0][i] == 0) {
				for (int j = 0; j < m.length; j++) {
					m[j][i] = 0;
				}
			}
		}
		print(m);

		System.out.println("Zero row");
		for (int i = 0; i < m.length; i++) {
			if (m[i][0] == 0) {
				for (int j = 0; j < m[0].length; j++) {
					m[i][j] = 0;
				}
			}
		}
		print(m);
	}
}
