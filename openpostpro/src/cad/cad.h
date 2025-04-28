#pragma once
#ifndef _CAD_H
#define _CAD_H

#include <shape.h>
#include <curve.h>
#include <Spline.h>

namespace cad
{
	/// <summary>
	/// Split a shape with intersection vectors in points
	/// </summary>
	/// <param name="shape"></param>
	/// <param name="points"></param>
	/// <returns></returns>
	std::vector<Shape*> split(Shape* shape, std::vector<glm::vec2> points);

	/// <summary>
	/// Split a polyline represented by coordinates with intersection vectors in points and vector indices for each pair of coordinates
	/// indices[0] contains indices of points[] that intersect with (coordinates[0],coordinates[1])
	/// </summary>
	/// <param name="coordinates"></param>
	/// <param name="points"></param>
	/// <param name="indices"></param>
	/// <returns></returns>
	std::vector<std::vector<glm::vec2>> split(std::vector<glm::vec2> coordinates, std::vector<glm::vec2> points, std::vector<std::vector<int>> indices);

	std::vector < std::vector<glm::vec2>> split(glm::vec2 p1, glm::vec2 p2, std::vector<glm::vec2> coordinates);

	/// <summary>
	/// Split at self intersections
	/// </summary>
	/// <param name="coordinates"></param>
	/// <returns></returns>
	std::vector<std::vector<glm::vec2>> split(std::vector<glm::vec2> coordinates);

	/// <summary>
	/// Split coordinates at each ref_point from points
	/// </summary>
	/// <param name="coordinates"></param>
	/// <param name="points"></param>
	/// <returns></returns>
	std::vector<std::vector<glm::vec2>> split(std::vector<glm::vec2> coordinates, std::vector<glm::vec2> points);

	std::vector<glm::vec2> get_raw_coordinates(std::vector<Shape*> shapes);

	std::string info(std::vector<Shape*> shapes);

	Curve to_curve(std::vector<Shape*> shapes);

	Curve to_curve(std::vector<glm::vec2> coordinates);

	Spline* to_spline(std::vector<Shape*> shapes, Renderer* render);
	
	Spline* to_spline(std::vector<glm::vec2> points, Renderer* render);

	std::vector<Shape*> chamfer(std::vector<Shape*> shapes, float radius);

	std::vector<Shape*> fillet(std::vector<Shape*> shapes, float radius);

	std::vector<Shape*> connected(Shape* s, std::vector<Shape*> shapes);

}

#endif