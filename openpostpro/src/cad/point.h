#pragma once

#include "shape.h"
#include <anchor.h>

#define POINT_SIZE 10.0f

class Point : public Shape
{
private:
	glm::vec2 _p1 = geometry::vec2_empty;	// coordinates
	Anchor* _a1 = nullptr;				// anchor on _p1
	float _scale = 0.0f;				// used to store actual scale factor as a ref_point is drawing with always the same size
	Buffer* _buffer = nullptr;			// vertices buffer for drawing

public:
	static float point_size;			// length of cross lines representing the ref_point

	// properties
	glm::vec2 p1();
	void p1(glm::vec2 value);

	// constructor
	Point(Renderer* r);
	~Point() override;
	Shape* clone() override;

	// overrides
	// Shape type
	GraphicType type() override { return GraphicType::Point; }

	// Matrix transformation
	void transform(glm::tmat4x4<float> mat) override;

	// mouse construction / modification
	void move(glm::vec2 point) override;
	bool point(glm::vec2 point) override;

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
	void scaled() override;
	void update() override;
	void draw() override;
	void draw_anchors() override;
	void ui() override;

	// IO
	std::string write() override;
	void read(std::string value, float version = 0) override;
};