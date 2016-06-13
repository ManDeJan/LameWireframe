// example:
// definition of the functions of a line class
// you are not expected to understand how line::print works

#include "line.hpp"

void line::print()
{
	int x0 = start_x, y0 = start_y;
	int x1 = end_x, y1 = end_y;
	int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
	int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
	int err = (dx>dy ? dx : -dy)/2, e2;

	for(;;) {
		w.draw(x0,y0);
		if (x0==x1 && y0==y1) break;
		e2 = err;
		if (e2 >-dx) {
			err -= dy;
			x0 += sx;
		}
		if (e2 < dy) {
			err += dx;
			y0 += sy;
		}
	}
}
