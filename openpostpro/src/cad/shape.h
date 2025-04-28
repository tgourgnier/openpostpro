#pragma once
#include <graphic.h>
#include <anchor.h>

#define PRECISION  5.0f

class Shape : public Graphic
{
private:
	bool _done = false;								// true if the shape is fully constructed
	Anchor* _modification_anchor = nullptr;			// hold current anchor that is manipulated
	std::string _parent;							// hold parent name
	int _tag = -1;

protected:
	bool _over = false;								// true if mouse is over
	geometry::rectangle _bounds;					// clip rectangle

public:
	// global variable to store the max distance to the shape for is_over method
	static float precision;

	int tag();
	void tag(int value);

	// properties
	std::string parent();
	void parent(std::string value);

	bool over();
	void over(bool value);

	geometry::rectangle& bounds();
	glm::vec2& topLeft();
	glm::vec2& bottomRight();

	// constructor/destructor
	Shape(Renderer* r) : Graphic(r) {}
	virtual ~Shape() {}
	virtual Shape* clone() { return nullptr; }

	virtual void reverse() {}

	virtual glm::vec2 first() { return glm::vec2(); }
	virtual void first(glm::vec2 value) {}
	virtual glm::vec2 last() { return glm::vec2(); }
	virtual void last(glm::vec2 value) {}

	// return anchor under ref_point
	virtual Anchor* anchor(glm::vec2 point) { return nullptr; }

	// return anchor under ref_point
	virtual std::vector<Anchor*> anchors() { return std::vector<Anchor*>(); }

	// ref_point is over shape
	virtual bool is_over(glm::vec2 point) { return false; }

	// return magnets ref_point to test, include anchors but can have more
	virtual std::vector<glm::vec2> magnets() { return std::vector<glm::vec2>(); }	

	void modification(Anchor* value) { _modification_anchor = value; }
	Anchor* modification() { return _modification_anchor; }

	virtual void move(glm::vec2 point) {}
	virtual bool point(glm::vec2 point) { return true; }
	virtual void done(bool value) { _done = value; }
	virtual bool done() { return _done; }

	virtual Shape* symmetry(glm::vec2 p1, glm::vec2 p2) { return nullptr; }
	virtual Shape* symmetry(glm::vec2 center) { return nullptr; }
};