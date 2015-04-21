// 5.8 A monochrome screen is stored as a single array of bytes, allowing eight
// consecutive pixels to be stored in one byte. The screen has width w, where w
// is divisible by 8 (that is, no byte will be split across rows). The height of
// the screen, of course, can be derived from the length of the array and the
// width. Implement a function drawHorizontalLine(byte[] screen, int width, int
// x1, int x2, int y) which draws a horizontal line from (x1,y) to (x2,y).
#include <iostream>
#include <vector>
using namespace std;
typedef unsigned char byte;

void drawHorizontalLine(vector<byte> &screen, int width, int x1, int x2, int y) {
	if(x1 > x2) return;
	const size_t wbytes = width >> 3;
	const int x1byte = (wbytes * y) + (x1 >> 3);
	if((x1byte < 0) || (x1byte >= int(screen.size()))) return;
	const int x2byte = (wbytes * y) + (x2 >> 3);
	if((x2byte < 0) || (x2byte >= int(screen.size()))) return;

	const byte ones = ~0;

	for(int i = x1byte; i <= x2byte; i ++)
		screen[i] = ones;

	int x1bit = x1 % 8;
	int x2bit = (x1bit + x2 - x1) % 8 + 1;
	screen[x1byte] &= ones << x1bit;
	screen[x2byte] &= ones >> (8 - x2bit);
}

void drawScreen(const vector<byte> &screen, int width) {
	for(size_t i = 0; i < screen.size(); i ++) {
		if((i % (width >> 3)) == 0)
			cout << endl;
		for(size_t b = 0; b < 8; b ++)
			cout << int((screen[i] >> b) & 1);
		cout << " ";
	}
	cout << endl;
}

void clearScreen(vector<byte> &screen, int width, int height) {
	screen.assign((width >> 3) * height, 0);
}

int main(void) {

	{ // Test 01
		vector<byte> screen;
		const int w = 2 * 8;
		const int h = 1;
		clearScreen(screen, w, h);

		for(int i = 0; i <= 15; i ++) {
			clearScreen(screen, w, h);
			drawHorizontalLine(screen, w, 0, i, 0);
			drawScreen(screen, w);
		}

		cout << endl << "-----------" << endl;

		for(int i = 0; i <= 15; i ++) {
			clearScreen(screen, w, h);
			drawHorizontalLine(screen, w, i, 15, 0);
			drawScreen(screen, w);
		}

		cout << endl << "-----------" << endl;

		for(int i = 0; i <= 15; i ++) {
			for(int j = i; j <=15; j ++) {
				clearScreen(screen, w, h);
				drawHorizontalLine(screen, w, i, j, 0);
				drawScreen(screen, w);
			}
		}
	}

	{ // Test 02
		vector<byte> screen;
		const int w = 5 * 8;
		const int h = 3;

		clearScreen(screen, w, h);
		drawHorizontalLine(screen, w, 13, 21, 1);
		drawScreen(screen, w);

		clearScreen(screen, w, h);
		drawHorizontalLine(screen, w, 0, 21, 1);
		drawScreen(screen, w);

		clearScreen(screen, w, h);
		drawHorizontalLine(screen, w, 13, 40, 1);
		drawScreen(screen, w);
	}

	return 0;
}
