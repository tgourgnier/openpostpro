#pragma once
#ifndef _OFFSET_H
#define _OFFSET_H

#include "toolpath.h"

class Offset : public Toolpath
{
private:
	bool _interior = true;

public:
	GraphicType type() override { return GraphicType::CamOffset; }

	Offset(Renderer* r) : Toolpath(r) {}

	bool interior() { return _interior; }
	void interior(bool value) { _interior = value; }
	
	bool start_point_allowed() override { return true; }

	void update() override;
	void scaled() override;
	std::vector<Curve> coordinates() override;

	void ui() override;

	// IO
	std::string write() override;
	void read(std::string value, float version = 0) override;
};

#endif