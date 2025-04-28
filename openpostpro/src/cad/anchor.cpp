#include "anchor.h"
#include <glm/ext.hpp>
#include "config.h"
#include <geometry.h>

Anchor::Anchor(Renderer* r) : Graphic(r) 
{
	_scale = r->camera()->scale();

	std::vector<glm::vec3> vertices{ 
		glm::vec3(),
		glm::vec3(),
		glm::vec3(),
		glm::vec3()
	};
	_triangles = _render->create_buffer(vertices);
}

Anchor::~Anchor()
{
	delete _triangles;
}

bool Anchor::is_over(glm::vec2 point)
{
	auto tl = glm::vec2(_point.x - ANCHOR_SIZE / _scale, _point.y + ANCHOR_SIZE / _scale);
	auto br = glm::vec2(_point.x + ANCHOR_SIZE / _scale, _point.y - ANCHOR_SIZE / _scale);
	return _is_over = geometry::rectangle_contains(
		tl,
		br,
		point
	) ;
}

void Anchor::update()
{
	std::vector<glm::vec3> vertices{
		glm::vec3(_point.x - ANCHOR_SIZE / _scale, _point.y - ANCHOR_SIZE / _scale, 0.0f),
		glm::vec3(_point.x - ANCHOR_SIZE / _scale, _point.y + ANCHOR_SIZE / _scale, 0.0f),
		glm::vec3(_point.x + ANCHOR_SIZE / _scale, _point.y - ANCHOR_SIZE / _scale, 0.0f),
		glm::vec3(_point.x + ANCHOR_SIZE / _scale, _point.y + ANCHOR_SIZE / _scale, 0.0f),
		glm::vec3(_point.x - (ANCHOR_SIZE + 2) / _scale, _point.y - (ANCHOR_SIZE + 2) / _scale, 0.0f),
		glm::vec3(_point.x - (ANCHOR_SIZE + 2) / _scale, _point.y + (ANCHOR_SIZE + 2) / _scale, 0.0f),
		glm::vec3(_point.x + (ANCHOR_SIZE + 2) / _scale, _point.y - (ANCHOR_SIZE + 2) / _scale, 0.0f),
		glm::vec3(_point.x + (ANCHOR_SIZE + 2) / _scale, _point.y + (ANCHOR_SIZE + 2) / _scale, 0.0f)
	};
	_triangles->flush(vertices);
}

void Anchor::draw()
{
	float scale = _render->camera()->scale();
	if (scale != _scale)
	{
		_scale = scale;
		update();
	}
	_render->set_uniform("inner_color", _is_over ? config.anchorOverFillColor : config.anchorFillColor);
	_triangles->draw(_render->pr_triangle_strip(), 0, 4);

	_render->set_uniform("inner_color", _is_over ? config.anchorOverLineColor : config.anchorLineColor);
	int indices[5]{ 0, 1, 3, 2, 0 };
	_triangles->draw(_render->pr_line_strip(), 5, indices);

	if (_is_over)
	{
		_render->set_uniform("inner_color", _is_over ? config.anchorOverLineColor : config.anchorLineColor);
		int indices[5]{ 4, 5, 7, 6, 4 };
		_triangles->draw(_render->pr_line_strip(), 5, indices);
	}
}
