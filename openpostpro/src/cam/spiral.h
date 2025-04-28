#pragma once
#ifndef _SPIRAL_H
#define _SPIRAL_H

#include "toolpath.h"

class Spiral : public Toolpath
{
public:
	GraphicType type() override { return GraphicType::CamSpiral; }

	Spiral(Renderer* r) : Toolpath(r) {}

	std::vector<Curve> coordinates() override;
};

#endif