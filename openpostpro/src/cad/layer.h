#pragma once
#include <string>
#include <vector>
#include "shape.h"
#include "graphic.h"

class Layer : public Graphic
{
private:
	std::vector<Shape*> _shapes;
	glm::vec4 _color;
	bool _visible = true;

public:
	std::vector<Shape*>& shapes() { return _shapes; }
	glm::vec4 color() { return _color; }
	void color(glm::vec4 color) { _color = color; }
	bool visible() { return _visible; }
	void visible(bool value) { _visible = value; }
	GraphicType type() override { return GraphicType::Layer; }

	void add(Shape* value);
	void remove(Shape* value);
	void remove(std::string name);
	void remove(unsigned int id);

	Shape* shape(std::string name);
	Shape* shape(unsigned int id);

	Layer(Renderer* r);
	~Layer();

	void reset(Renderer* r) override;
	void scaled() override;
	void draw() override;
	void ui() override;
	void draw_anchors() override;

	// IO
	std::string write() override;
	void read(std::string value, float version = 0) override;
};