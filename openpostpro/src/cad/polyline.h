#pragma once
#ifndef _POLYLINE_H
#define _POLYLINE_H

#include "shape.h"
#include <anchor.h>

enum class PolylineMode
{
	Polyline,
	BSpline,
	NaturalCubic,
	lagrange,
	Catmull,
	Bezier
};

class Polyline : public Shape
{
private:
	std::vector<glm::vec2> _points;					// array of control points
	std::vector<glm::vec2> _coordinates;			// array of points to display
	std::vector<Anchor*> _anchors;					// array of anchors
	Buffer* _buffer = nullptr;						// vertices buffer for drawing
	PolylineMode _mode = PolylineMode::Polyline;	// type of polyline to display
	bool _transform = false;						// true if a transformation is applied
	int count = 0;
	bool _move = false;

public:
	//properties
	std::vector<glm::vec2> points() { return _points; }
	void points(std::vector<glm::vec2> points);
	PolylineMode mode() { return _mode; }
	void mode(PolylineMode value) { if (value != _mode) { _mode = value; if (_points.size() > 2) update(); } }

	// constructor/destructor
	Polyline(Renderer* r);
	~Polyline() override;
	Shape* clone() override;

	std::vector<glm::vec2> coordinates();

	void reverse() override;

	glm::vec2 first() override;
	void first(glm::vec2 value) override;
	glm::vec2 last() override;
	void last(glm::vec2 value) override;

	// overrides
	// Shape type
	GraphicType type() override { return GraphicType::Polyline; }

	// Matrix transformation
	void transform(glm::tmat4x4<float> mat) override;

	// mouse construction / modification
	void move(glm::vec2 point) override;
	bool point(glm::vec2 point) override;
	void done(bool value) override;
	bool done() override;

	// ref_point is over shape
	bool is_over(glm::vec2 point) override;

	// return anchor under ref_point
	Anchor* anchor(glm::vec2 point) override;

	// return anchor under ref_point
	virtual std::vector<Anchor*> anchors() override;

	// return magnet points
	std::vector<glm::vec2> magnets() override;

	// construction
	Shape* symmetry(glm::vec2 p1, glm::vec2 p2) override;
	Shape* symmetry(glm::vec2 center) override;

	// display
	void compute() override;
	void update() override;
	void draw() override;
	void draw_anchors() override;
	void ui() override;

	// IO
	std::string write() override;
	void read(std::string value, float version = 0) override;
};

#endif