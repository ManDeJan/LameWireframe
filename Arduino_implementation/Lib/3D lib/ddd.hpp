/**
 * \file
 * \brief		3D header.
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

#pragma once

#include "hwlib.hpp"

/**
 * \brief Vertex structure to store 3D coordinates
 *
 * This has 3 floats for storing X, Y and Z
 */
struct Vertex {
	float x, y, z;
};

/**
 * \brief Edge struct to connect 2 Vertexes
 *
 * It just stores which vertexes in an array of vertexes are connected
 */
struct Edge {
	unsigned char first, second;
};

/**
 * \brief The main class, it can manipulate and draw 3d objects
 */
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

	/**
	 * \brief This is the decorator of the main class, it is a 3d object you can draw on 2d windows.
	 *
	 * \param w A hwlib window referenice where the object will be printed on.
	 * \param vertices An array of vertices that make up the 3d object.
	 * \param edges An array of edges that tell the object which vertices are connected.
	 * \param verticelength the amount of vertices.
	 * \param edgelength the amount of edges.
	 * \param screenwidth the width of the screen so that (0,0) is the middle of the screen.
	 * \param screenheight the height of the screen so that (0,0) is the middle of the screen.
	 */
	driedobj( hwlib::window & w, Vertex vertices[], Edge edges[], unsigned char verticelength, unsigned char edgelength, unsigned int screenwidth, unsigned int screenheight):
		w (w),
		verticelength (verticelength),
		edgelength (edgelength),
		screenwidthoffset (screenwidth/2),
		screenheightoffset (screenheight/2),
		vertices (vertices),
		edges (edges)
	{};

	/// Rotate the object over the X-axis with x amount of degrees.
	void rotateX(float degrees);

	/// Rotate the object over the Y-axis with x amount of degrees.
	void rotateY(float degrees);

	/// Rotate the object over the Z-axis with x amount of degrees.
	void rotateZ(float degrees);

	/// Translate the object (move it around the world) by adding or subtracting its x y and z coordinates.
	void translate(float x, float y, float z);

	/// Scale the object to make it bigger or smaller.
	void scale(float scale);

	/// Print the object on the screen
	void draw();

};
