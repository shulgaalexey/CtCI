// Eight Queens: Write an algorithm to print all ways of arranging eight queens on an 8x8 chess board
// so that none of them share the same row, column, or diagonal. In this case, "diagonal" means all
// diagonals, not just the two that bisect the board.
import java.util.*;

public class Task_8_12 {

	static int GRID_SIZE = 8;

	static void placeQueens(int row, Integer[] columns, ArrayList<Integer[]> results) {
		if (row == GRID_SIZE) {
			results.add(columns.clone());
		} else {
			for (int col = 0; col < GRID_SIZE; col++) {
				if (checkValid(columns, row, col)) {
					columns[row] = col;
					placeQueens(row + 1, columns, results);
				}
			}
		}
	}

	static boolean checkValid(Integer[] columns, int row1, int column1) {
		for (int row2 = 0; row2 < row1; row2++) {
			int column2 = columns[row2];

			if (column1 == column2) {
				return false;
			}

			int columnDistance = Math.abs(column2 - column1);
			int rowDistance = row1 - row2;
			if (columnDistance == rowDistance) {
				return false;
			}
		}
		return true;
	}

	public static void main(String args[]) {
		Integer[] columns = new Integer[8];
		ArrayList<Integer[]> results = new ArrayList<>();
		placeQueens(0, columns, results);

		Map<String, Integer> m = new HashMap<>();
		for (Integer[] res: results) {
			StringBuilder sb = new StringBuilder();
			for (int i = 0; i < res.length; i++) {
				sb.append("" + res[i] + " ");
			}
			String str = sb.toString();
			System.out.println(str);
			if (!m.containsKey(str)) {
				m.put(str, 1);
			} else {
				m.put(str, m.get(str) + 1);
				System.out.println("DUPLICATE");
			}
		}
		//System.out.println(m);
	}
}
