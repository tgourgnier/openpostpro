#pragma once
#include "graphic.h"
#include <toolpath.h>

enum class CoolingType
{
	None,
	Flood,
	Mist
};

enum class ToolRadiusCompensation
{
	None,
	Left,
	Right
};

class Group : public Graphic
{
private:
	std::vector<Toolpath*> _toolpaths;
	glm::vec4 _color;
	bool _visible = true;
	bool _generate = true;
	int _tool_number = -1;
	float _tool_radius = 1;
	ToolRadiusCompensation _tool_radius_compensation = ToolRadiusCompensation::None;
	int _tool_length_compensation = -1;
	bool _cw = true;
	float _feed = 1000;
	float _finition_offset = 0.5f;
	float _finition_feed = 1000;
	float _plung_feed = 500;
	float _pass = 1;
	float _origin = 0;
	float _depth = -3;
	float _safe = 5;
	float _spindle_speed = 0;
	bool _spindle_cw = true;
	CoolingType _cooling = CoolingType::None;
	float _dwell = 0;
	float _back_position = 5;
	std::string _pre_command = "";
	std::string _post_command = "";
	StartPointType _start_point_type = StartPointType::normal;
	float _start_point_offset = 0;
	int _repeat_x = 0;
	float _repeat_x_offset = 10;
	int _repeat_y = 0;
	float _repeat_y_offset = 10;

public:
	std::vector<Toolpath*>& toolpaths() { return _toolpaths; }
	glm::vec4 color() { return _color; }
	void color(glm::vec4 color) { _color = color; }
	bool visible() { return _visible; }
	void visible(bool value) { _visible = value; }
	bool generate() { return _generate; }
	void generate(bool value) { _generate = value; }
	GraphicType type() override { return GraphicType::Group; }

	float tool_radius() { return _tool_radius; }
	void tool_radius(float value);

	ToolRadiusCompensation tool_radius_compensation() { return _tool_radius_compensation; }
	void tool_radius_compensation(ToolRadiusCompensation value) { _tool_radius_compensation = value; }

	int tool_length_compensation() { return _tool_length_compensation; }
	void tool_length_compensation(int value) { _tool_length_compensation = value; }

	bool cw() { return _cw; }
	void cw(bool value);

	bool spindle_cw() { return _spindle_cw; }
	void spindle_cw(bool value) { _spindle_cw = value; }

	float spindle_speed() { return _spindle_speed; }
	void spindle_speed(float value) { _spindle_speed = value; }

	int tool_number() { return _tool_number; }
	void tool_number(int value) { _tool_number = value; }

	float safe() { return _safe; }
	void safe(float value) { _safe = value; }

	float feed() { return _feed; }
	void feed(float value) { _feed = value; }

	float finition_feed() { return _finition_feed; }
	void finition_feed(float value) { _finition_feed = value; }

	float plung_feed() { return _plung_feed; }
	void plung_feed(float value) { _plung_feed = value; }

	float pass() { return _pass; }
	void pass(float value) { _pass = value; }
	
	float origin() { return _origin; }
	void origin(float value) { _origin = value; }

	float depth() { return _depth; }
	void depth(float value) { _depth = value; }

	std::string pre_command() { return _pre_command; }
	void pre_command(std::string value) { _pre_command = value; }

	std::string post_command() { return _post_command; }
	void post_command(std::string value) { _post_command = value; }


	StartPointType start_point_type() { return _start_point_type; }
	void start_point_type(StartPointType value);

	float start_point_offset() { return _start_point_offset; }
	void start_point_offset(float value);

	Group(Renderer* r);
	~Group();

	void add(Toolpath* value);
	void remove(Toolpath* value);
	void remove(std::string name);
	void remove(unsigned int id);

	Toolpath* toolpath(std::string name);
	Toolpath* toolpath(unsigned int id);

	void reset(Renderer* r) override;
	void scaled() override;
	void ui() override;
	void draw() override;

	// IO
	std::string write() override;
	void read(std::string value, float version = 0) override;
};