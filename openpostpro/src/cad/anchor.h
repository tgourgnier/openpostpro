#pragma once
#include <graphic.h>
#include <geometry.h>

#define ANCHOR_SIZE 2.5f

class Anchor : public Graphic
{
private:
	glm::vec2 _point = geometry::vec2_empty;
	float _scale;
	Buffer* _triangles;
	bool _is_over = false;

public:
	glm::vec2 point() { return _point; }
	void point(glm::vec2 value) { _point = value; update(); }

	Anchor(Renderer* r);
	~Anchor();

	bool is_over(glm::vec2 point);

	void update() override;
	void draw() override;
};