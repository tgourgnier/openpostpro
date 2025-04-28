#pragma once
#ifndef _GRAPHIC_H
#define _GRAPHIC_H

#include "graphic.h"



void Graphic::name(std::string n)
{
	//if (!_name.empty() && _name != n) 
	//	History::undo(HistoryActionType::Modify, write()); 
	_name = n;
}

bool Graphic::shape()
{
	return (int)type() >= 100 && (int)type() < 200;
}

bool Graphic::toolpath()
{
	return (int)type() >= 200 && (int)type() < 300;
}

void Graphic::compute()
{
	_needs_update = true;
}

void Graphic::scaled()
{

}

void Graphic::draw()
{
	if (_needs_update)
	{
		_needs_update = false;
		update();
	}
}



#endif
