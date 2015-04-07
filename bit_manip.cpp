// 5. Bits manipulations
#include <iostream>
using namespace std;

bool get_bit(const int num, const int i) {
	return (num & (1 << i));
}

int set_bit(int num, const int i) {
	return (num | (1 << i));
}

int clear_bit(int num, const int i) {
	return (num & ~(1 << i));
}

int clear_bits_msb_through_i(int num, const int i)  { // including i
	int mask = (1 << i) -1;
	return (num & mask);
}

int clear_bits_i_through_0(int num, const int i) { // including i
	int mask = (~1) << i;
	return (num & mask);
}

int update_bit(int num, const int i, const int v) {
	num &= ~(1 << i); // clear the specified bit
	return (num | (v << i));
}

int main(void) {
	bool ok = true;

	ok &= get_bit(0b10110, 4);
	ok &= !get_bit(0b10110, 3);
	ok &= set_bit(0b10110, 0) == 0b10111;
	ok &= clear_bit(0b10101, 2) == 0b10001;
	ok &= clear_bits_msb_through_i(0b11111, 2) == 0b00011;
	ok &= clear_bits_i_through_0(0b11111, 2) == 0b11000;
	ok &= update_bit(0b10101, 2, 0) == 0b10001;
	ok &= update_bit(0b10001, 2, 1) == 0b10101;
	ok &= update_bit(0b10101, 2, 1) == 0b10101;

	if(!ok) cout << "PROBLEM!" << endl;
	return 0;
}
