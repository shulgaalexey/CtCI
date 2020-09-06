// 1.6 Given an image representing by NxN matrix, where each pixel in the image is 4 bytes,
// write a method to rotate the image by 90 degrees.
// Can you do this in place?
import java.util.*;

public class Task_1_6 {
	static void print(char [][] image, int N) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				System.out.print(image[i][j]);
			}
			System.out.println();
		}
	}

	static void rotateCircle(char [][] from, char [][] to, int offset, int N) {
		int side = N - 2 * offset - 1;
		int len = side * 4;
		int x1 = 0;
		int y1 = 0;
		int x2 = 0;
		int y2 = 0;

		char prev = 'x';
		for (int i = 0; i < len; i++) {
			int sideNo = i / side;
			switch (sideNo) {
				case 0:
					x1 = i % side;
					y1 = 0;
					x2 = side;
					y2 = i % side;
					break;
				case 1:
					x1 = side;
					y1 = i % side;
					x2 = side - i % side;
					y2 = side;
					break;
				case 2:
					x1 = side - i % side;
					y1 = side;
					x2 = 0;
					y2 = side - i % side;
					break;
				case 3:
					x1 = 0;
					y1 = side - i % side;
					x2 = i % side;
					y2 = 0;
					break;
			}
			x1 += offset;
			y1 += offset;
			x2 += offset;
			y2 += offset;

			to[y2][x2] = from[y1][x1];
		}
	}


	static char [][] rotate(char [][] image, int N) {

		char [][] to = new char[N][N];
		for (int i = 0; i < N / 2; i++) {
			rotateCircle(image, to, i, N);
		}
		return to;
	}

	public static void main(String args[]) {
		final int N = 4;
		char [][] image = new char[][] {
			{'a', 'b', 'c', 'd'},
			{'e', 'f', 'g', 'h'},
			{'i', 'j', 'k', 'l'},
			{'m', 'n', 'o', 'p'}
		};
		print(image, N);

		// Expecting:
		/*char [][] image2 = new char[][] {
			{'m', 'i', 'e', 'a'},
			{'n', 'j', 'f', 'b'},
			{'o', 'k', 'g', 'c'},
			{'p', 'l', 'h', 'd'}
		};*/

		System.out.println("Rotating...");
		char [][] res = rotate(image, N);
		print(res, N);
	}
}
