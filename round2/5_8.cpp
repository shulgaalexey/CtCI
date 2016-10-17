#include <iostream>
using namespace std;

typedef unsigned char byte;

void draw_horz_line(byte *screen, int width, int x1, int x2, int y) {

	int byte_pos1 = y * width / 8 + x1 / 8;
	int bit_pos1 = 7 - x1 % 8;

	int byte_pos2 = y * width / 8 + x2 / 8;
	int bit_pos2 = 7 - x2 % 8;

	if(byte_pos1 == byte_pos2) { // Line is in the single byte
		byte mask = (0xFF << (bit_pos2 + 1)) >> (7 - bit_pos1);
		screen[byte_pos1] = mask;
		return;
	}

	screen[byte_pos1] = 0xFF >> (7 - bit_pos1);

	for(int i = (byte_pos1 + 1); i < byte_pos2; i ++)
		screen[i] = 0xFF;

	screen[byte_pos2] = 0xFF << (bit_pos2 + 1);
}

int main(void) {
	byte screen[64] = {0};

	draw_horz_line(screen, 64, 3, 17, 2);
	//draw_horz_line(screen, 64, 0, 9, 0);

	for(int i = 0; i < 8; i ++) {
		for(int j = 0; j < 8; j ++) {
			int cur8 = screen[i * 8 + j];
			for(int k = 7; k >= 0; k --) {
				if(cur8 & 0x80)
					cout << '-';
				else
					cout << '#';
				cur8 <<= 1;
			}
		}
		cout << endl;
	}
	cout << endl;

	return 0;
}
