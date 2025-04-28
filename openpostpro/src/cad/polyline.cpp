#include "polyline.h"
#include "geometry.h"
#include "imgui.h"
#include <logger.h>
#include <lang.h>
#include <config.h>
#include <future>
#include <strings.h>
#include <history.h>


Polyline::Polyline(Renderer* r) : Shape(r)
{
	//std::vector<glm::vec3> vertices{ glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f) };
	//_data_buffer = r->create_buffer(vertices);
}

Polyline::~Polyline()
{
	// deleting anchors
	for (Anchor* a : _anchors)
		delete a;
	_anchors.clear();

	// deleting graphic buffer
	_render->delete_buffer(_buffer);
}

Shape* Polyline::clone()
{
	Polyline* p = new Polyline(_render);
	for (auto c : _points)
		p->point(c);
	p->mode(_mode);
	p->done(true);
	p->compute();
	return p;
}


void Polyline::points(std::vector<glm::vec2> points)
{
	//if (done())
	//	History::undo(HistoryActionType::Modify, write());

	_points.clear();
	_points.insert(_points.end(), points.begin(), points.end());
	done(true);
	compute();
}

void Polyline::reverse()
{
	std::reverse(_points.begin(), _points.end());
	compute();
}

std::vector<glm::vec2> Polyline::coordinates()
{
	return _coordinates;
}

void Polyline::transform(glm::tmat4x4<float> mat)
{
	for (int i = 0; i < _points.size(); i++)
		_points[i] = mat * glm::vec4(_points[i].x, _points[i].y, 1, 1);
	for (int i = 0; i < _coordinates.size(); i++)
		_coordinates[i] = mat * glm::vec4(_coordinates[i].x, _coordinates[i].y, 1, 1);
	_transform = true;
	compute();
}

glm::vec2 Polyline::first()
{
	return _coordinates.front();
}

void Polyline::first(glm::vec2 value)
{
	if (_points.size() > 0)
	{
		_points[0] = value;
		compute();
	}
}

glm::vec2 Polyline::last()
{
	return _coordinates.back();
}

void Polyline::last(glm::vec2 value)
{
	if (_points.size() > 0)
	{
		_points[_points.size()-1] = value;
		compute();
	}
}

void Polyline::move(glm::vec2 point)
{
	if (done())
	{
		for (int i = 0; i < _anchors.size(); i++)
		{
			if (_anchors[i] == modification())
			{
				_points[i] = glm::vec2(point.x, point.y);
			}
		}
	}
	else
	{
		_move = true;
		if (_points.size() > 1)
			_points[_points.size() - 1] = point;
	}
	compute();
}

bool Polyline::point(glm::vec2 point)
{
	if (_points.size() == 0)
		_points.push_back(point);
	_points.push_back(point);
	if (_mode == PolylineMode::Bezier && _points.size() == 4)
	{
		done(true);
		return true;
	}
	compute();
	return false;
}


void Polyline::done(bool value)
{
	if (done() != value)
	{
		Shape::done(value);

		if (value && _move)
		{
			switch (_mode)
			{
			case PolylineMode::Polyline:
			case PolylineMode::BSpline:
			case PolylineMode::lagrange:
			case PolylineMode::Catmull:
			case PolylineMode::NaturalCubic:
				if (_points.size() > 2)
					_points.pop_back();
				break;
			case PolylineMode::Bezier:
				if (_points.size() > 4)
					_points.pop_back();
				break;
			}
			compute();
		}
		_move = false;
	}
}

bool Polyline::done()
{
	return Shape::done();
}

bool Polyline::is_over(glm::vec2 point)
{
	auto p = PRECISION * 2;
	// check if distance of first ref_point to mouse is less than precision
	if (glm::distance(_points.front(), point) < p)
		return true;
	// check if distance of last ref_point to mouse is less than precision
	if (glm::distance(_points.back(), point) < p)
		return true;
	// check if mouse inside clip and if distance "mouse to the line" is less than precision
	if (_bounds.offset(p).contains(point)) {
		auto last = _points.front();
		for (int i = 1; i < _points.size(); i++)
		{
			auto next = _points.at(i);
			if (geometry::foretriangle(last, next, point) < p)
			{
				if (glm::distance(last, point) + glm::distance(next, point) - glm::distance(last, next) < p)
					return true;
			}
			last = next;
		}
		last = _coordinates.front();
		for (int i = 1; i < _coordinates.size(); i++)
		{
			auto next = _coordinates.at(i);
			if (geometry::foretriangle(last, next, point) < p)
			{
				if (glm::distance(last, point) + glm::distance(next, point) - glm::distance(last, next) < p)
					return true;
			}
			last = next;
		}
	}
	return false;
}


Anchor* Polyline::anchor(glm::vec2 point)
{
	for (Anchor* a : _anchors)
		if (a->is_over(point))
			return a;
	return nullptr;
}

std::vector<Anchor*> Polyline::anchors()
{
	return _anchors;
}

std::vector<glm::vec2> Polyline::magnets()
{
	std::vector<glm::vec2> m;
	if (done())
	{
		for (Anchor* a : _anchors)
			m.push_back(a->point());
	}
	else
	{
		if (_points.size() > 1)
		{
			for (int i = 0; i < _points.size() - 1; i++)
				m.push_back(_points[i]);
		}
	}
	return m;
}

Shape* Polyline::symmetry(glm::vec2 p1, glm::vec2 p2)
{
	Polyline* p = new Polyline(_render);
	for (auto c : _points)
		p->point(geometry::symmetry(c, p1, p2));
	p->mode(_mode);
	p->done(true);
	p->compute();
	return p;
}

Shape* Polyline::symmetry(glm::vec2 center)
{
	Polyline* p = new Polyline(_render);
	for (auto c : _points)
		p->point(geometry::symmetry(c, center));
	p->mode(_mode);
	p->done(true);
	p->compute();
	return p;
}

void Polyline::compute()
{
	if (done())
	{
		// update clip rect
		_bounds.max();

		if (_points.size() < 2)
			return;

		for (glm::vec2 p : _points)
		{
			_bounds.top_left.x = glm::min(_bounds.top_left.x, p.x);
			_bounds.top_left.y = glm::max(_bounds.top_left.y, p.y);
			_bounds.bottom_right.x = glm::max(_bounds.bottom_right.x, p.x);
			_bounds.bottom_right.y = glm::min(_bounds.bottom_right.y, p.y);
		}

		/*_top_left.x -= PRECISION;
		_top_left.y += PRECISION;
		_bottom_right.x += PRECISION;
		_bottom_right.y -= PRECISION;*/

		// update vertices
		if (!_transform)
		{
			switch (_mode) {
			case PolylineMode::Polyline:
				_coordinates = _points;
				break;
			case PolylineMode::Bezier:
				_coordinates = geometry::bezier(_points, 0.5f);
				break;
			case PolylineMode::BSpline:
				_coordinates = geometry::bspline(_points);
				break;
			case PolylineMode::lagrange:
				_coordinates = geometry::lagrange(_points);
				break;
			case PolylineMode::Catmull:
				_coordinates = geometry::catmull(_points);
				break;
			case PolylineMode::NaturalCubic:
				_coordinates = geometry::naturalCubic(_points);
				break;
			}
		}
		_transform = false;
	}
	else if (_points.size() > 0)
	{
		std::vector<glm::vec3> vertices;
		switch (_mode) {
		case PolylineMode::Polyline:
			_coordinates = _points;
			break;
		case PolylineMode::Bezier:
			if (_points.size() == 4)
				_coordinates = geometry::bezier(_points, 0.5f);
			break;
		case PolylineMode::BSpline:
			if (_points.size() > 2)
				_coordinates = geometry::bspline(_points);
			break;
		case PolylineMode::lagrange:
			if (_points.size() > 2)
				_coordinates = geometry::lagrange(_points);
			break;
		case PolylineMode::Catmull:
			if (_points.size() > 2)
				_coordinates = geometry::catmull(_points);
			break;
		case PolylineMode::NaturalCubic:
			if (_points.size() > 2)
				_coordinates = geometry::naturalCubic(_points);
			break;
		}
	}

	Graphic::compute();
}


void Polyline::update()
{
	if (done())
	{
		std::vector<glm::vec3> vertices;
		for (glm::vec2 v : _coordinates)
			vertices.push_back(glm::vec3(v.x, v.y, 0));

		if (_buffer == nullptr)
			_buffer = _render->create_buffer(vertices);
		else
			_buffer->flush(vertices);

		// to do : anchors must be limited following precision and not arbitrary
		if (_points.size() < 100 && _mode == PolylineMode::Polyline || _mode != PolylineMode::Polyline)
		{
			for (int i = 0; i < _points.size(); i++)
			{
				if (i < _anchors.size())
					_anchors[i]->point(_points[i]);
				else
				{
					_anchors.push_back(new Anchor(_render));
					_anchors.back()->point(_points[i]);
				}
			}
			// shrink anchors
			if (_anchors.size() > _points.size())
			{
				for (int i = (int)_anchors.size() - 1; i > (int)_points.size(); i--)
				{
					delete _anchors[i];
				}
				_anchors.resize(_points.size());
			}
		}
		else
		{
			for(auto a : _anchors)
				delete a;
			_anchors.clear();
			auto a = new Anchor(_render);
			a->point(_points.front());
			_anchors.push_back(a);
			a = new Anchor(_render);
			a->point(_points.back());
			_anchors.push_back(a);
		}
	}
	else if (_points.size() > 0)
	{
		std::vector<glm::vec3> vertices;
		
		for (glm::vec2 v : _points)
			vertices.push_back(glm::vec3(v.x, v.y, 0));
		for (glm::vec2 v : _coordinates)
			vertices.push_back(glm::vec3(v.x, v.y, 0));
		if (_buffer == nullptr)
			_buffer = _render->create_buffer(vertices);
		else
			_buffer->flush(vertices);
	}
}

void Polyline::draw()
{
	Graphic::draw();

	if (_buffer == nullptr) return;

	if (!done())
	{
		if (_points.size() <= _buffer->size())
			_buffer->draw(_render->pr_line_strip(), 0, (int)_points.size());

		if (_buffer->size() - _points.size() > 0)
			_buffer->draw(_render->pr_line_strip(), (int)_points.size(), (int)(_buffer->size() - _points.size()));
	}
	else if (_buffer->size() > 2)
		_buffer->draw(_render->pr_line_strip());
}

void Polyline::draw_anchors()
{
	// draw anchors
	if (_selected)
	{
		for (Anchor* a : _anchors)
		{
			a->draw();
		}
	}
}

void Polyline::ui()
{
	ImGui::Begin((_name + "###OBJECT").c_str());
	ImGui::BeginTable("##TABLE_OBJECT", 2, ImGuiTableFlags_SizingFixedFit);
	ImGui::TableSetupColumn("##COL0", ImGuiTableColumnFlags_WidthFixed);
	ImGui::TableSetupColumn("##COL1", ImGuiTableColumnFlags_WidthStretch);

	ImGui::TableNextRow();
	ImGui::TableSetColumnIndex(0);
	ImGui::Spacing();
	ImGui::Text(Lang::l("NB_POINTS"));
	ImGui::TableSetColumnIndex(1);
	ImGui::Spacing();
	ImGui::Text(std::to_string(_points.size()).c_str());


	ImGui::TableNextRow();
	ImGui::TableSetColumnIndex(0);
	ImGui::Spacing();
	ImGui::Text(Lang::l("MODE"));
	ImGui::TableSetColumnIndex(1);
	ImGui::PushItemWidth(-FLT_MIN);
	const char* items[]{ "Poly","Bezier"/*,"BSpline"*/, "Natural Cubic", "Lagrange" };
	int selected_item = (int)_mode;
	if (ImGui::Combo("##MODE", &selected_item, items, IM_ARRAYSIZE(items)))
	{
		mode((PolylineMode)selected_item);
		compute();
		update();
	}

	char input[20];

	size_t max = 10;
	for (size_t i = 0; i < _points.size()&& i < max; i++)
	{
		ImGui::TableNextRow();
		sprintf_s(input, "%0.3f;%0.3f", _points[i].x, _points[i].y);
		ImGui::TableSetColumnIndex(0);
		ImGui::Spacing();
		ImGui::Text((std::string("Point_") + std::to_string(i+1)).c_str());
		ImGui::TableSetColumnIndex(1);
		ImGui::PushItemWidth(-FLT_MIN);
		if (ImGui::InputText((std::string("##LP") + std::to_string(i)).c_str(), input, 20 * sizeof(char), ImGuiInputTextFlags_EnterReturnsTrue))
		{
			std::string val = input;
			auto numbers = stringex::split(val, ';');
			auto p = _points[i];
			if (numbers.size() == 2)
			{
				try
				{
					p.x = std::stof(numbers[0]);
					p.y = std::stof(numbers[1]);
					if (p != _points[i])
					{
						History::undo(HistoryActionType::Modify, write());
						_points[i] = p;
						compute();
					}
				}
				catch (const std::exception& e)
				{
					Logger::log(e.what());
				}
			}
		}
	}
	if (_points.size() > max)
	{
		ImGui::TableNextRow();
		sprintf_s(input, "%0.3f;%0.3f", _points.back().x, _points.back().y);
		ImGui::TableSetColumnIndex(0);
		ImGui::Spacing();
		ImGui::Text((std::string("Point_") + std::to_string(_points.size())).c_str());
		ImGui::TableSetColumnIndex(1);
		ImGui::PushItemWidth(-FLT_MIN);
		if (ImGui::InputText("##LP_LAST", input, 20 * sizeof(char), ImGuiInputTextFlags_EnterReturnsTrue))
		{
			std::string val = input;
			auto numbers = stringex::split(val, ';');
			auto p = _points.back();
			if (numbers.size() == 2)
			{
				try
				{
					p.x = std::stof(numbers[0]);
					p.y = std::stof(numbers[1]);
					if (p != _points.back())
					{
						History::undo(HistoryActionType::Modify, write());
						_points.pop_back();
						_points.push_back(p);
						compute();
					}
				}
				catch (const std::exception& e)
				{
					Logger::log(e.what());
				}
			}
		}
	}

	ImGui::EndTable();
	ImGui::End();
}

std::string Polyline::write()
{
	std::string result =
		std::to_string((short)type()) + ';' +
		std::to_string(id()) + ';' +
		parent() + ';' +
		_name + ';' +
		std::to_string((int)_mode) + ';' +
		std::to_string((int)_points.size()) + ';';
		

	for (glm::vec2 p : _points)
		result += stringex::to_string(p.x) + ';' + stringex::to_string(p.y) + ';';

	return result.substr(0, result.size() - 1);
}

void Polyline::read(std::string value, float version)
{
	_points.clear();
	auto data = stringex::split(value, ';');
	if (data.size() >= 5)
	{
		// data[0] = type
		_id = (unsigned int)std::stoi(data[1]);
		parent(data[2]);
		_name = data[3];
		_mode = (PolylineMode)std::stoi(data[4]);
		auto count = std::stoi(data[5]);
		int i = 0, j=6;
		while (i++ < count)
		{
			_points.push_back(glm::vec2(
				std::stof(data[j]),
				std::stof(data[j+1])
			));
			j += 2;
		}
		done(true);
		compute();
	}
}