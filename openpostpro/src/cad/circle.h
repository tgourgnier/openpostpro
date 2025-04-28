#pragma once

#include "shape.h"
#include <anchor.h>

class Circle : public Shape
{
private:
	glm::vec2 _center = geometry::vec2_empty;	// center coordinates
	float _radius = 10.0f;					// circle radius

	Anchor* _a1 = nullptr;
	Anchor* _a2 = nullptr;

	std::vector<glm::vec3> _vertices;
	Buffer* _buffer = nullptr;

public:
	// properties
	glm::vec2 center() { return _center; }
	void center(glm::vec2 p);
	float radius() { return _radius; }
	void radius(float r);
	void set(glm::vec2 p, float r);

	// constructor/destructor
	Circle(Renderer* r);
	~Circle() override;
	Shape* clone() override;

	// overrides
	// Shape type
	GraphicType type() override { return GraphicType::Circle; }

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
	void update() override;
	void draw() override;
	void draw_anchors() override;
	void ui() override;

	// IO
	std::string write() override;
	void read(std::string value, float version = 0) override;
};

