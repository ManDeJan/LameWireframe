#include "window.hpp"
#include "line.hpp"
#include <cmath>
#include <cstdlib>
#include "ddd.hpp"

int main()
{
	unsigned int width = 128;
	unsigned int height = 64;
	window w( width, height, 1 );

	size_t verticeslength = 8;
	size_t edgelength = 12;

	Vertex vertices[] = {
		{ 16,  16,  16},
		{ 16,  16, -16},
		{ 16, -16,  16},
		{-16,  16,  16},
		{ 16, -16, -16},
		{-16,  16, -16},
		{-16, -16,  16},
		{-16, -16, -16},
	};

	Edge edges[] = {
		{0, 1},
		{0, 2},
		{0, 3},
		{1, 4},
		{1, 5},
		{2, 4},
		{2, 6},
		{3, 5},
		{3, 6},
		{4, 7},
		{5, 7},
		{6, 7},
	};

	Vertex pyrverts[] = {
		{ 10,  0,  10},
		{-10,  0,  10},
		{ 10,  0, -10},
		{-10,  0, -10},
		{  0, 25,   0},
	};

	Edge pyredge[] = {
		{0, 1},
		{0, 2},
		{1, 3},
		{2, 3},
		{0, 4},
		{1, 4},
		{2, 4},
		{3, 4},
	};


	driedobj cube(w, vertices, edges, verticeslength, edgelength, width, height);
	driedobj pyramid(w, pyrverts, pyredge, 5, 8, width, height);

	pyramid.rotateZ(1.5);
	pyramid.translate(64, 0, 0);
	cube.rotateZ(1);
	cube.rotateY(1);

	while (true) {

		pyramid.translate(-1, 0, 0);
		cube.rotateZ(0.002);
		cube.rotateY(0.005);
		cube.rotateX(0.002);
		pyramid.rotateX(0.1);
		//if(pyramid.posx < -100){pyramid.posx=100;}
		pyramid.draw();
		cube.draw();
		w.mainloop();
		w.clear();
	}
}
