// Paint Fill: Implement the "paint fill" function that one might see on many image editing programs.
// That is, given a screen (represented by a two-dimensional array of colors), a point, and a new color,
// fill in the surrounding area until the color changes from the original color.
import java.util.*;

public class Task_8_10 {

	static void print(char[][] screen) {
		System.out.println("----------------");
		for (int i = 0; i < screen.length; i++) {
			for (int j = 0; j < screen[i].length; j++) {
				System.out.print("" + screen[i][j] + ' ');
			}
			System.out.println();
		}
		System.out.println("----------------");
	}
	static class Point {
		int y;
		int x;
		Point(int y, int x) {
			this.y = y;
			this.x = x;
		}
		Point top() {
			return new Point(y - 1, x);
		}
		Point left() {
			return new Point(y, x - 1);
		}
		Point bottom() {
			return new Point(y + 1, x);
		}
		Point right() {
			return new Point(y, x + 1);
		}
	}
	static boolean isValid(final Point pt, final char[][] screen) {
		return pt.y >= 0 && pt.y < screen.length && pt.x >= 0 && pt.x < screen[0].length;
	}
	static char getColor(final Point pt, final char[][] screen) {
		return screen[pt.y][pt.x];
	}
	static void refill(final char[][] screen, final int y, final int x, final char color) {
		final char touch = screen[y][x];
		System.out.println("" + touch);
		Deque<Point> q = new LinkedList<>();
		q.offer(new Point(y, x));
		while (!q.isEmpty()) {
			Point pt = q.poll();
			screen[pt.y][pt.x] = color;
			if (isValid(pt.top(), screen) && getColor(pt.top(), screen) == touch) {
				q.offer(pt.top());
			}
			if (isValid(pt.left(), screen) && getColor(pt.left(), screen) == touch) {
				q.offer(pt.left());
			}
			if (isValid(pt.bottom(), screen) && getColor(pt.bottom(), screen) == touch) {
				q.offer(pt.bottom());
			}
			if (isValid(pt.right(), screen) && getColor(pt.right(), screen) == touch) {
				q.offer(pt.right());
			}
		}
	}
	public static void main(String args[]) {
		char [][] screen = {
			{'r', 'r', 'r', 'r', 'r', 'r', 'r', 'r'},
			{'r', 'r', 'r', 'r', 'r', 'r', 'r', 'r'},
			{'r', 'r', 'r', 'r', 'r', 'b', 'b', 'r'},
			{'r', 'r', 'r', 'r', 'r', 'b', 'b', 'r'},
			{'r', 'r', 'r', 'r', 'r', 'r', 'r', 'r'},
			{'r', 'r', 'r', 'G', 'r', 'r', 'r', 'r'},
			{'r', 'r', 'G', 'G', 'G', 'r', 'r', 'G'},
			{'r', 'G', 'G', 'b', 'G', 'G', 'G', 'G'},
			{'r', 'r', 'G', 'G', 'G', 'G', 'G', 'G'},
			{'r', 'r', 'r', 'G', 'r', 'r', 'r', 'G'},
			{'r', 'r', 'r', 'r', 'r', 'r', 'r', 'r'},
			{'r', 'r', 'r', 'r', 'r', 'r', 'r', 'r'},
			{'r', 'b', 'b', 'r', 'r', 'b', 'b', 'r'},
			{'r', 'r', 'r', 'r', 'r', 'b', 'b', 'r'},
			{'r', 'r', 'r', 'r', 'r', 'r', 'r', 'r'},
		};
		print(screen);
		refill(screen, 7, 6, '#');
		print(screen);
	}
}
