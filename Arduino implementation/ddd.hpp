#pragma once

#include "hwlib.hpp"
struct Vertex {
	float x, y, z;
};

struct Edge {
	unsigned char first, second;
};

class driedobj
{
private:
	hwlib::window & w;
	unsigned char verticelength, edgelength;
	unsigned int screenwidthoffset, screenheightoffset;

public:
	Vertex *vertices;
	Edge *edges;
	float posx = 0, posy = 0, posz = 0;

	driedobj( hwlib::window & w, Vertex vertices[], Edge edges[], unsigned char verticelength, unsigned char edgelength, unsigned int screenwidth, unsigned int screenheight):
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
