#pragma once
#ifndef _FOLLOW_H
#define _FOLLOW_H

#include "toolpath.h"

class Follow : public Toolpath
{
private:

public:
	GraphicType type() override { return GraphicType::CamFollow; }
	
	Follow(Renderer* r) : Toolpath(r) {}

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