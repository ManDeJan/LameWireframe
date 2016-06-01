#include "window.hpp"
#include <cstdlib>
#pragma once

struct Vertex {
	float x, y, z;
};

struct Edge {
	size_t first, second;
};

class driedobj
{
private:
	window & w;
	size_t verticelength, edgelength;
	unsigned int screenwidthoffset, screenheightoffset;

public:
	Vertex *vertices;
	Edge *edges;
	float posx = 0, posy = 0, posz = 0;

	driedobj( window & w, Vertex vertices[], Edge edges[], size_t verticelength, size_t edgelength, unsigned int screenwidth, unsigned int screenheight):
		w (w),
		verticelength (verticelength),
		edgelength (edgelength),
		screenwidthoffset (screenwidth/2),
		screenheightoffset (screenheight/2),
		vertices (vertices),
		edges (edges)
	{};
	void rotateX(float degrees);
	void rotateY(float degrees);
	void rotateZ(float degrees);
	void translate(float x, float y, float z);
	void scale(float scale);
	void draw();

};
