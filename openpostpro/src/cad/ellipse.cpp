#include "ellipse.h"
#include "geometry.h"
#include "imgui.h"
#include "lang.h"
#include "strings.h"
#include "logger.h"
#include "config.h"
#include <glm/gtx/transform.hpp>
#include <history.h>


Ellipse::Ellipse(Renderer* r) : Shape(r)
{
	std::vector<glm::vec3> vertices{ glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f) };
	_buffer = r->create_buffer(vertices);

	_a1 = new Anchor(r);
	_a2 = new Anchor(r);
	_a3 = new Anchor(r);

	_start = 0.0f;
	_stop = 2 * glm::pi<float>();
}

Ellipse::~Ellipse()
{
	// deleting anchors
	delete _a1;
	delete _a2;
	delete _a3;

	// deleting graphic buffer
	_render->delete_buffer(_buffer);
}

Shape* Ellipse::clone()
{
	Ellipse* e = new Ellipse(_render);
	e->center(_center);
	e->minor(_minor);
	e->major(_major);
	e->angle(_angle);
	e->done(true);
	e->compute();
	return e;
}

std::vector<glm::vec2> Ellipse::coordinates()
{
	return _coordinates;
}

void Ellipse::reverse()
{
	//_angle = -_angle;
	//auto p = _start;
	//_start = _stop;
	//_stop = p;
	//compute();
}

void Ellipse::center(glm::vec2 value)
{
	if (_center != value)
	{
		//if (done())
		//	History::undo(HistoryActionType::Modify, write());

		_center = value;
		if (_minor > 0 && _major > 0)
		{
			done(true);
			compute();
		}
	}
}

void Ellipse::start(float value)
{
	if (_start != value)
	{
		//if (done())
		//	History::undo(HistoryActionType::Modify, write());

		_start = value;
		if (_minor > 0 && _major > 0)
		{
			done(true);
			compute();
		}
	}
}

void Ellipse::stop(float value)
{
	if (_stop != value)
	{
		//if (done())
		//	History::undo(HistoryActionType::Modify, write());

		_stop = value;
		if (_minor > 0 && _major > 0)
		{
			done(true);
			compute();
		}
	}
}

void Ellipse::minor(float value)
{
	if (_minor != value)
	{
		//if (done())
		//	History::undo(HistoryActionType::Modify, write());

		_minor = value;
		if (_minor > 0 && _major > 0)
		{
			done(true);
			compute();
		}
	}
}

void Ellipse::major(float value)
{
	if (_major != value)
	{
		//if (done())
		//	History::undo(HistoryActionType::Modify, write());

		_major = value;
		if (_minor > 0 && _major > 0)
		{
			done(true);
			compute();
		}
	}
}

void Ellipse::angle(float value)
{
	if (_angle != value)
	{
		//if (done())
		//	History::undo(HistoryActionType::Modify, write());

		_angle = value;
		if (_minor > 0 && _major > 0)
		{
			done(true);
			compute();
		}
	}
}

void Ellipse::set(glm::vec2 center, float minor, float major, float start, float stop, float angle)
{
	if (_center != center || _minor != minor || _major != major || _start != start || _stop != stop || _angle != angle)
	{
		//if (done())
		//	History::undo(HistoryActionType::Modify, write());

		_center = center;
		_minor = minor;
		_major = major;
		_start = start;
		_stop = stop;
		_angle = angle;
		if (_minor > 0 && _major > 0)
		{
			done(true);
			compute();
		}
	}
}

Anchor* Ellipse::anchor(glm::vec2 point)
{
	if (_a1->is_over(point))
		return _a1;
	if (_a2->is_over(point))
		return _a2;
	if (_a3->is_over(point))
		return _a3;
	return nullptr;
}

std::vector<Anchor*> Ellipse::anchors()
{
	return std::vector<Anchor*>({_a1, _a2, _a3});
}

std::vector<glm::vec2> Ellipse::magnets()
{
	std::vector<glm::vec2> points;
	if (done())
	{
		if (modification() == nullptr)
		{
			points.push_back(_center);
			points.push_back(_a2->point());
			points.push_back(_a3->point());
			points.push_back(geometry::symmetry(_a2->point(), _center));
			points.push_back(geometry::symmetry(_a3->point(), _center));
		}
	}
	else
		points.push_back(_center);

	return points;
}

Shape* Ellipse::symmetry(glm::vec2 p1, glm::vec2 p2)
{
	Ellipse* e = new Ellipse(_render);
	e->center(geometry::symmetry(_center, p1, p2));
	e->minor(_minor);
	e->major(_major);
	e->angle(_angle);
	e->done(true);
	e->compute();
	return e;
}

Shape* Ellipse::symmetry(glm::vec2 center)
{
	Ellipse* e = new Ellipse(_render);
	e->center(geometry::symmetry(_center, center));
	e->minor(_minor);
	e->major(_major);
	e->angle(_angle);
	e->done(true);
	e->compute();
	return e;
}

void Ellipse::transform(glm::tmat4x4<float> mat)
{
	_center = mat * glm::vec4(_center.x, _center.y, 1, 1);
	compute();
}

void Ellipse::move(glm::vec2 point)
{
	if (done())
	{
		if (_a1 == modification())
			_center = point;
		else if (_a2 == modification())
		{
			auto pmin = geometry::position(glm::half_pi<float>() + _angle, _minor / 2.0f, _center);
			auto projection = geometry::projection(point, _center, pmin);
			if (projection.y != point.y)
				_minor = _minor;
			_minor = glm::distance(_center, projection) * 2;
		}
		else if (_a3 == modification())
		{
			auto pmaj = geometry::position(_angle, _major / 2.0f, _center);
			auto projection = geometry::projection(point, _center, pmaj);
			_major = glm::distance(_center, projection) * 2;
		}
	}
	else if (_center != geometry::vec2_empty)
	{
		if (_major == -1)
		{
			_vertices[1] = glm::vec3(point, 0.0f);
		}
		else
		{
			auto h = geometry::position(_angle + glm::half_pi<float>(), 100.0f, _center);
			auto p = geometry::projection(point, _center, h);
			_minor = glm::distance(_center, p) * 2.0f;
		}
	}
	compute();
}

bool Ellipse::point(glm::vec2 point)
{
	if (_center == geometry::vec2_empty)
	{
		_center = point;
		_vertices.push_back(glm::vec3(_center, 0.0f));
		_vertices.push_back(glm::vec3(_center, 0.0f));
	}
	else if (_major == -1)
	{
		_major = glm::distance(_center, point);
		_center = geometry::middle(_center, point);
		_angle = geometry::oriented_angle(point, _center);
	}
	else
	{
		auto h = geometry::position(_angle + glm::half_pi<float>(), 100.0f, _center);
		auto p = geometry::projection(point, _center, h);
		_minor = glm::distance(_center, p) * 2.0f;
		done(true);
		compute();
		return true;
	}
	return false;
}


bool Ellipse::is_over(glm::vec2 point)
{
	if (_a1->is_over(point))
		return true;
	for (glm::vec3 p : _vertices)
	{
		if (geometry::distance2(point, p) < PRECISION)
			return true;
	}
	return false;
}

void Ellipse::compute()
{
	if (done())
	{
		_coordinates = geometry::ellipse(_center, _minor, _major, _start, _stop, _angle, 0.5f);

		// update clip rect
		_bounds.max();
		for (glm::vec2 p : _coordinates)
		{
			_bounds.top_left.x = (glm::min)(_bounds.top_left.x, p.x);
			_bounds.top_left.y = (glm::max)(_bounds.top_left.y, p.y);
			_bounds.bottom_right.x = (glm::max)(_bounds.bottom_right.x, p.x);
			_bounds.bottom_right.y = (glm::min)(_bounds.bottom_right.y, p.y);
		}

		// update vertices
		//std::vector<glm::vec3> vertices;
		_vertices.clear();
		for (glm::vec2 v : _coordinates)
			_vertices.push_back(glm::vec3(v.x, v.y, 0));

		// add vertices to draw selected lines
		auto pmin = geometry::position(glm::half_pi<float>() + _angle, _minor / 2.0f, _center);
		auto pmaj = geometry::position(_angle, _major / 2.0f, _center);
		_vertices.push_back(glm::vec3(pmin, 0.0f));
		_vertices.push_back(glm::vec3(geometry::symmetry(pmin, _center), 0.0f));
		_vertices.push_back(glm::vec3(geometry::symmetry(pmaj, _center), 0.0f));
		_vertices.push_back(glm::vec3(pmaj, 0.0f));
	}
	else if (_center != geometry::vec2_empty)
	{
		if (_major != -1)
		{
			_vertices.clear();
			std::vector<glm::vec2> coordinates = geometry::ellipse(_center, _minor, _major, _start, _stop, _angle, 0.5f);
			for (glm::vec2 v : coordinates)
				_vertices.push_back(glm::vec3(v.x, v.y, 0));
		}
	}

	Graphic::compute();
}

void Ellipse::update()
{
	if (done())
	{
		if (_buffer == nullptr)
			_buffer = _render->create_buffer(_vertices);
		else
			_buffer->flush(_vertices);

		auto pmin = geometry::position(glm::half_pi<float>() + _angle, _minor / 2.0f, _center);
		auto pmaj = geometry::position(_angle, _major / 2.0f, _center);

		_a1->point(_center);
		_a2->point(pmin);
		_a3->point(pmaj);
	}
	
	if (_vertices.size() > 1)
	{
		if (_buffer == nullptr)
			_buffer = _render->create_buffer(_vertices);
		else
			_buffer->flush(_vertices);
	}
}

void Ellipse::draw()
{
	Graphic::draw();

	if (_buffer->size() < 4)
		_buffer->draw(_render->pr_lines());
	else
		_buffer->draw(_render->pr_line_strip(), 0, (int)_buffer->size() - 4);
}

void Ellipse::draw_anchors()
{
	// draw anchors
	if (_selected)
	{
		if (config.show_decoration)
		{
			_render->set_uniform("inner_color", config.decorationColor);
			_buffer->draw(_render->pr_lines(), (int)_buffer->size() - 4, 4);
		}

		_a1->draw();
		_a2->draw();
		_a3->draw();
	}
}

void Ellipse::ui()
{
	char input[20];

	ImGui::Begin((_name + "###OBJECT").c_str());
	ImGui::BeginTable("##TABLE_OBJECT", 2, ImGuiTableFlags_SizingFixedFit);
	ImGui::TableSetupColumn("##COL0", ImGuiTableColumnFlags_WidthFixed);
	ImGui::TableSetupColumn("##COL1", ImGuiTableColumnFlags_WidthStretch);


	ImGui::TableNextRow();
	sprintf_s(input, "%0.3f,%0.3f", _center.x, _center.y);
	ImGui::TableSetColumnIndex(0);
	ImGui::Spacing();
	ImGui::Text(Lang::l("CENTER"));
	ImGui::TableSetColumnIndex(1);
	ImGui::PushItemWidth(-FLT_MIN);
	if (ImGui::InputText("##CENTER", input, 20 * sizeof(char), ImGuiInputTextFlags_EnterReturnsTrue))
	{
		std::string val = input;
		auto numbers = stringex::split(val, ';');
		auto point = _center;
		if (numbers.size() == 2)
		{
			try
			{
				point.x = std::stof(numbers[0]);
				point.y = std::stof(numbers[1]);
				if (point != _center)
				{
					History::undo(HistoryActionType::Modify, write());
					center(point);
				}
			}
			catch (const std::exception& e)
			{
				Logger::log(e.what());
			}
		}
	}

	ImGui::TableNextRow();
	sprintf_s(input, "%.3f", _minor);
	ImGui::TableSetColumnIndex(0);
	ImGui::Spacing();
	ImGui::Text(Lang::l("MINOR"));
	ImGui::TableSetColumnIndex(1);
	if (ImGui::InputText("##MINOR", input, 20 * sizeof(char), ImGuiInputTextFlags_EnterReturnsTrue))
	{
		try
		{
			auto m = std::stof(input);
			if (m != _minor)
			{
				History::undo(HistoryActionType::Modify, write());
				minor(m);
			}
		}
		catch (const std::exception& e)
		{
			Logger::log(e.what());
		}
	}

	ImGui::TableNextRow();
	sprintf_s(input, "%.3f", _major);
	ImGui::TableSetColumnIndex(0);
	ImGui::Spacing();
	ImGui::Text(Lang::l("MAJOR"));
	ImGui::TableSetColumnIndex(1);
	if (ImGui::InputText("##MAJOR", input, 20 * sizeof(char), ImGuiInputTextFlags_EnterReturnsTrue))
	{
		try
		{
			auto m = std::stof(input);
			if (m != _major)
			{
				History::undo(HistoryActionType::Modify, write());
				major(m);
			}
		}
		catch (const std::exception& e)
		{
			Logger::log(e.what());
		}
	}

	ImGui::TableNextRow();
	sprintf_s(input, "%.3f", glm::degrees(_start));
	ImGui::TableSetColumnIndex(0);
	ImGui::Spacing();
	ImGui::Text(Lang::l("START_ANGLE"));
	ImGui::TableSetColumnIndex(1);
	if (ImGui::InputText("##START_ANGLE", input, 20 * sizeof(char), ImGuiInputTextFlags_EnterReturnsTrue))
	{
		try
		{
			auto a = glm::radians(std::stof(input));
			if (a != _start)
			{
				History::undo(HistoryActionType::Modify, write());
				start(a);
			}
		}
		catch (const std::exception& e)
		{
			Logger::log(e.what());
		}
	}

	ImGui::TableNextRow();
	sprintf_s(input, "%.3f", glm::degrees(_stop));
	ImGui::TableSetColumnIndex(0);
	ImGui::Spacing();
	ImGui::Text(Lang::l("STOP_ANGLE"));
	ImGui::TableSetColumnIndex(1);
	if (ImGui::InputText("##STOP_ANGLE", input, 20 * sizeof(char), ImGuiInputTextFlags_EnterReturnsTrue))
	{
		try
		{
			auto a = glm::radians(std::stof(input));
			if (a != _stop)
			{
				History::undo(HistoryActionType::Modify, write());
				stop(a);
			}
		}
		catch (const std::exception& e)
		{
			Logger::log(e.what());
		}
	}

	ImGui::TableNextRow();
	sprintf_s(input, "%.3f", glm::degrees(_angle));
	ImGui::TableSetColumnIndex(0);
	ImGui::Spacing();
	ImGui::Text(Lang::l("ANGLE"));
	ImGui::TableSetColumnIndex(1);
	if (ImGui::InputText("##ANGLE", input, 20 * sizeof(char), ImGuiInputTextFlags_EnterReturnsTrue))
	{
		try
		{
			auto a = glm::radians(std::stof(input));
			if (a != _angle)
			{
				History::undo(HistoryActionType::Modify, write());
				angle(a);
			}
		}
		catch (const std::exception& e)
		{
			Logger::log(e.what());
		}
	}

	ImGui::EndTable();
	ImGui::End();
}

std::string Ellipse::write()
{
	return
		std::to_string((short)type()) + ';' +
		std::to_string(id()) + ';' +
		parent() + ';' +
		_name + ';' +
		stringex::to_string(_center.x) + ';' +
		stringex::to_string(_center.y) + ';' +
		stringex::to_string(_major) + ';' +
		stringex::to_string(_minor) + ';' +
		stringex::to_string(_start) + ';' +
		stringex::to_string(_stop) + ';' +
		stringex::to_string(_angle);
}

void Ellipse::read(std::string value, float version)
{
	auto data = stringex::split(value, ';');
	if (data.size() == 11)
	{
		// data[0] = type
		_id = (unsigned int)std::stoi(data[1]);
		parent(data[2]);
		_name = data[3];
		_center.x = std::stof(data[4]);
		_center.y = std::stof(data[5]);
		_major = std::stof(data[6]);
		_minor = std::stof(data[7]);
		_start = std::stof(data[8]);
		_stop = std::stof(data[9]);
		_angle = std::stof(data[10]);

		done(true);
		compute();
	}
}