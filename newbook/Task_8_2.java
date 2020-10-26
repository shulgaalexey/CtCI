// Robot in a Grid: Imagine a robot sitting on the upper left corner of grid with r rows and c columns.
// The robot can only move in two directions, right and down, but certain cells are "off limits" such that
// the robot cannot step on them. Design an algorithm to find a path for the robot from the top left to
// the bottom right.
import java.util.*;

public class Task_8_2 {
	static class Cell {
		int y;
		int x;
		Cell(int y, int x) {
			this.y = y;
			this.x = x;
		}
		@Override
		public String toString() {
			return "" + y + "," + x;
		}
	}

	static void print(char[][] grid) {
		for (int i = 0; i < (grid[0].length + 2); i++) {
			System.out.print('-');
		}
		System.out.println();
		for (int i = 0; i < grid.length; i++) {
			System.out.print('|');
			for (int j = 0; j < grid[i].length; j++) {
				System.out.print(grid[i][j]);
			}
			System.out.print('|');
			System.out.println();
		}
		for (int i = 0; i < (grid[0].length + 2); i++) {
			System.out.print('-');
		}
		System.out.println();
	}

	public static void main2(String args[]) {
		final int c = 5;
		final int r = 8;

		char[][] grid = new char[r][c];

		for (int i = 0; i < grid.length; i++) {
			for (int j = 0; j < grid[i].length; j++) {
				grid[i][j] = '`';
			}
		}

		grid[0][2] = '#';
		grid[2][1] = '#';
		grid[2][2] = '#';
		grid[2][2] = '#';
		grid[4][1] = '#';
		grid[5][1] = '#';
		grid[5][0] = '#';
		grid[5][3] = '#';
		grid[5][4] = '#';
		grid[6][3] = '#';
		print(grid);

		Deque<Cell> q = new LinkedList<>();
		q.offer(new Cell(r - 1, c - 1));
		grid[r - 1][c - 1] = 'F';
		while (!q.isEmpty()) {
			Cell cur = q.poll();
			Cell top = new Cell(cur.y - 1, cur.x);
			if (top.y >= 0 && grid[top.y][top.x] == '`') {
				grid[top.y][top.x] = 'v';
				q.offer(top);
			}
			Cell left = new Cell(cur.y, cur.x - 1);
			if (left.x >= 0 && grid[left.y][left.x] == '`') {
				grid[left.y][left.x] = '>';
				q.offer(left);
			}
		}
		print(grid);

		if (grid[0][0] == '`') {
			System.out.println("No way!");
			return;
		}

		List<Cell> way = new ArrayList<>();
		way.add(new Cell(0, 0));
		while (true) {
			Cell last = way.get(way.size() - 1);
			if (grid[last.y][last.x] == 'v') {
				Cell next = new Cell(last.y + 1, last.x);
				way.add(next);
			} else if (grid[last.y][last.x] == '>') {
				Cell next = new Cell(last.y, last.x + 1);
				way.add(next);
			} else if (grid[last.y][last.x] == 'F') {
				break;
			} else {
				throw new IllegalStateException("Wrong cell on my way!");
			}
		}
		print(grid);

		System.out.println(way);

		for (Cell cur: way) {
			grid[cur.y][cur.x] = '*';
		}
		print(grid);
	}

	// Book'a approach
	static Set<Cell> failed = new HashSet<>();
	static List<Cell> path = new ArrayList<>();

	static boolean getPath(char[][] grid, int y, int x) {
		if (y < 0 || x < 0 || grid[y][x] == '#') {
			return false;
		}

		Cell c = new Cell(y, x);

		if (failed.contains(c)) {
			return false;
		}

		if ((y == 0 && x == 0) || getPath(grid, y - 1, x)|| getPath(grid, y, x - 1)) {
			path.add(c);
			return true;
		}

		failed.add(c);
		return false;
	}

	public static void main(String args[]) {
		final int c = 5;
		final int r = 8;

		char[][] grid = new char[r][c];

		for (int i = 0; i < grid.length; i++) {
			for (int j = 0; j < grid[i].length; j++) {
				grid[i][j] = '`';
			}
		}

		grid[0][2] = '#';
		grid[2][1] = '#';
		grid[2][2] = '#';
		grid[2][2] = '#';
		grid[4][1] = '#';
		grid[5][1] = '#';
		grid[5][0] = '#';
		grid[5][3] = '#';
		grid[5][4] = '#';
		grid[6][3] = '#';
		print(grid);


		getPath(grid, r - 1, c - 1);

		System.out.println(path);
		for (Cell cur: path) {
			grid[cur.y][cur.x] = '*';
		}
		print(grid);
	}
}
