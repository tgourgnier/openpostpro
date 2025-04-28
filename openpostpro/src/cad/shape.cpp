#include <shape.h>
#include <history.h>

float Shape::precision = PRECISION;

int Shape::tag()
{
	return _tag;
}

void Shape::tag(int value)
{
	_tag = value;
}

std::string Shape::parent()
{
	return _parent;
}

void Shape::parent(std::string value)
{
	if (_parent != value )
	{
		_parent = value;
		//if (done())
		//	History::undo(HistoryActionType::Modify, write());
	}
}

bool Shape::over()
{
	return _over;
}

void Shape::over(bool value)
{
	_over = value;
}

geometry::rectangle& Shape::bounds()
{
	return _bounds;
}

glm::vec2& Shape::topLeft()
{
	return _bounds.top_left;
}

glm::vec2& Shape::bottomRight()
{
	return _bounds.bottom_right;
}
