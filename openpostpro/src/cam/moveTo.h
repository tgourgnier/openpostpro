#pragma once
#ifndef _MOVETO_H
#define _MOVETO_H

#include "toolpath.h"

#define _MOVE_TO_SIZE 10

class MoveTo : public Toolpath
{
private:
	int _pause;

public:
	GraphicType type() override { return GraphicType::CamMoveTo; }

	void pause(int value) { _pause = value; }
	int pause() { return _pause; }

	glm::vec2 point() { return _original[0][0].point; }
	void point(glm::vec2 value) { _original[0][0].point = value; }

	MoveTo(Renderer* r);
	~MoveTo();

	std::vector<Curve> coordinates() override;
	void compute() override;
	void scaled() override;
	void ui() override;
	void draw() override;

	// IO
	std::string write() override;
	void read(std::string value, float version = 0) override;
};

#endif