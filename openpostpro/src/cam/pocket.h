#pragma once
#ifndef _POCKET_H
#define _POCKET_H

#include "toolpath.h"

enum class PocketMode
{
	Zigzag,
	Offset
};

class Pocket : public Toolpath
{
private:
	std::vector<int> _indices;
	bool _climb = true;
	PocketMode _mode = PocketMode::Offset;
	float _finishing = 0.0f;

public:
	GraphicType type() override { return GraphicType::CamPocket; }

	Pocket(Renderer* r) : Toolpath(r) {}

	PocketMode mode() { return _mode; }
	void mode(PocketMode value);

	float finishing() const { return _finishing; }
	void finishing(float value);

	bool climb() { return _climb; }
	void climb(bool value) { _climb = value; }

	std::vector<Curve> zigzag(std::vector<Curve>& curves);
	std::vector<Curve> offset(std::vector<Curve>& curves);
	std::vector<Curve> merge(std::vector<Curve>& curves);

	void update() override;
	void scaled() override;
	std::vector<Curve> coordinates() override;

	void ui() override;
};

#endif