/**
 * \file
 * \author		Jan Halsema
 * \copyright	Copyright (c) 2016, Jan Halsema
 *
 * \page License
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "due_sam3x.h"
#include "ddd.hpp"
#include "hwlib.hpp"
#include "easymath.h"

void driedobj::rotateX(float degrees)
{
	float sinT = sin(degrees);
	float cosT = cos(degrees);
	float y = 0, z = 0;

	for(unsigned int v = 0; v < verticelength; v++) {
		y = vertices[v].y;
		z = vertices[v].z;
		vertices[v].y = (y * cosT) - (z * sinT);
		vertices[v].z = (z * cosT) + (y * sinT);
	}
}

void driedobj::rotateY(float degrees)
{
	float sinT = sin(degrees);
	float cosT = cos(degrees);
	float x = 0, z = 0;

	for(unsigned int v = 0; v < verticelength; v++) {
		x = vertices[v].x;
		z = vertices[v].z;
		vertices[v].x = (x * cosT) - (z * sinT);
		vertices[v].z = (z * cosT) + (x * sinT);
	}
}

void driedobj::rotateZ(float degrees)
{
	float sinT = sin(degrees);
	float cosT = cos(degrees);
	float x = 0, y = 0;

	for(unsigned int v = 0; v < verticelength; v++) {
		x = vertices[v].x;
		y = vertices[v].y;
		vertices[v].x = (x * cosT) - (y * sinT);
		vertices[v].y = (y * cosT) + (x * sinT);
	}
}
void driedobj::translate(float x, float y, float z)
{
	posx += x;
	posy += y;
	posz += z;
}

void driedobj::scale(float scale)
{
	for(unsigned int i = 0; i < verticelength; i++) {
		vertices[i].x *= scale;
		vertices[i].y *= scale;
		vertices[i].z *= scale;
	}
}

void driedobj::draw()
{
	float p1 = 1, p2 = 1;
	for(unsigned int e = 0; e < edgelength; e++) {
		p1 = 80/(vertices[edges[e].first].z/4+posz+80);
		p2 = 80/(vertices[edges[e].second].z/4+posz+80);

		hwlib::line(hwlib::location{ (vertices[edges[e].first].x+posx)*p1 + screenwidthoffset, (vertices[edges[e].first].y+posy)*p1 + screenheightoffset }, hwlib::location{ (vertices[edges[e].second].x+posx)*p2 + screenwidthoffset, (vertices[edges[e].second].y+posy)*p2 + screenheightoffset }).draw(w);
		//line(w, (vertices[edges[e].first].x+posx)*p1 + screenwidthoffset, (vertices[edges[e].first].y+posy)*p1 + screenheightoffset, (vertices[edges[e].second].x+posx)*p2 + screenwidthoffset, (vertices[edges[e].second].y+posy)*p2 + screenheightoffset).print();
		// remove // below to debug stuff! :D
		//printf("%1f %f %f %f\n", vertices[edges[e][0]][0]*scale + 64, vertices[edges[e][0]][1]*scale + 32, vertices[edges[e][1]][0]*scale + 64, vertices[edges[e][1]][1]*scale + 32);
		//printf("%f %f\n", vertices[edges[e][0]][2], vertices[edges[e][1]][2]);
	}
}
