// 9.7 Implement the "paint fill" function that one might see on many image
// editing programs. That is, given a screen (represented by a two-dimensional
// array of colors), a point, and a new color, fill in the surrounding area
// untli the color changes from the original color.
#include <iostream>
#include <queue>
#include <stdexcept>
using namespace std;

typedef unsigned char COLOR;
const COLOR UNDEF_COLOR = -1;
COLOR *_SCREEN = NULL;
int _WIDTH = 0;
int _HEIGHT = 0;


class point {
	public:
		int x;
		int y;
	public:
		point() : x(0), y(0) {}
		point(int X, int Y) : x(X), y(Y) {}
	public:
		bool valid() const {
			if((x < 0) || (y < 0)) return false;
			if((x >= _WIDTH) || (y >= _HEIGHT)) return false;
			return true;
		}
};

COLOR get_color(const point &pt) {
	if(!pt.valid()) return UNDEF_COLOR;
	return _SCREEN[_WIDTH * pt.y + pt.x];
}

void set_color(const point &pt, COLOR new_color) {
	if(!pt.valid())
		throw out_of_range("set_color out of range");
	_SCREEN[_WIDTH * pt.y + pt.x] = new_color;
}

point get_top(point pt) {
	pt.y --;
	return pt;
}

point get_bottom(point pt) {
	pt.y ++;
	return pt;
}

point get_right(point pt) {
	pt.x ++;
	return pt;
}

point get_left(point pt) {
	pt.x --;
	return pt;
}

void paint_fill(int x, int y, COLOR new_color) {
	const point the_point(x, y);
	if(!the_point.valid())
		throw out_of_range("paint_fill out of range");
	const COLOR origin_color = get_color(the_point);
	queue<point> q;
	q.push(the_point);
	while(!q.empty()) {
		point pt = q.front();
		q.pop();
		set_color(pt, new_color);
		if(get_top(pt).valid() && (get_color(get_top(pt)) == origin_color))
			q.push(get_top(pt));
		if(get_bottom(pt).valid() && (get_color(get_bottom(pt)) == origin_color))
			q.push(get_bottom(pt));
		if(get_right(pt).valid() && (get_color(get_right(pt)) == origin_color))
			q.push(get_right(pt));
		if(get_left(pt).valid() && (get_color(get_left(pt)) == origin_color))
			q.push(get_left(pt));
	}
}

void draw_screen(const char *caption) {
	cout << caption << endl;
	for(int i = 0; i < _HEIGHT; i ++) {
		for(int j = 0; j < _WIDTH; j ++)
			cout << int(_SCREEN[i * _WIDTH + j]) << " ";
		cout << endl;
	}
	cout << endl;
}

int main(void) {
	_WIDTH = 8;
	_HEIGHT = 6;

	COLOR screen[] = {
		2, 1, 1, 1, 3, 3, 3, 2,
		1, 1, 1, 2, 2, 3, 3, 3,
		1, 1, 2, 2, 2, 0, 0, 0,
		4, 4, 2, 2, 2, 2, 2, 0,
		4, 2, 2, 2, 1, 1, 2, 0,
		2, 4, 4, 4, 1, 1, 1, 2
	};
	_SCREEN = screen;
	//draw_screen("Initial screen");

	COLOR new_screen[] = {
		2, 1, 1, 1, 3, 3, 3, 2,
		1, 1, 1, 3, 3, 3, 3, 3,
		1, 1, 3, 3, 3, 0, 0, 0,
		4, 4, 3, 3, 3, 3, 3, 0,
		4, 3, 3, 3, 1, 1, 3, 0,
		2, 4, 4, 4, 1, 1, 1, 2
	};
	_SCREEN = new_screen;
	//draw_screen("Expected screen");


	_SCREEN = screen;
	paint_fill(3, 2, 3);
	//draw_screen("Result screen");

	COLOR error_screen[] = {
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
	};
	for(int i = 0; i < (_WIDTH * _HEIGHT); i ++ ) {
		if(_SCREEN[i] != new_screen[i]) {
			cout << "ERROR!" << endl;
			cout << int(_SCREEN[i]) << "!=" << int(new_screen[i]) << endl;
			cout << int(i % _WIDTH) << "," << int(i / _WIDTH) << endl;
			//break;
			error_screen[i] = new_screen[i];
		}
	}
	_SCREEN = error_screen;
	//draw_screen("Error screen");

	return 0;
}
