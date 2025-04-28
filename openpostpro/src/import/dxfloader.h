/************************************************************************
* OpenPostPro - www.openpostpro.org
* -----------------------------------------------------------------------
* Copyright(c) 2024 Thomas Gourgnier
*
* This software is provided 'as-is', without any express or implied
* warranty.In no event will the authors be held liable for any damages
* arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions :
*
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software.If you use this software
*    in a product, an acknowledgment in the product documentation would
*    be appreciated but is not required.
*
* 2. Altered source versions must be plainly marked as such, and must not
*    be misrepresented as being the original software.
*
* 3. This notice may not be removed or altered from any source
*    distribution.
*
*************************************************************************/

/************************************************************************
* Convert Dxf data into OpenPostPro dbjects
*************************************************************************/

#pragma once
#include <string>
#include <document.h>
#include "dxf.h"

class DxfLoader
{
public:
	static int _count;
	static std::vector<Shape*> add_entity(DxfEntity* e, Renderer* r);
	static std::vector<Shape*> add_line(DxfEntity* e, Renderer* r);
	static std::vector<Shape*> add_point(DxfEntity* e, Renderer* r);
	static std::vector<Shape*> add_circle(DxfEntity* e, Renderer* r);
	static std::vector<Shape*> add_arc(DxfEntity* e, Renderer* r);
	static std::vector<Shape*> add_ellipse(DxfEntity* e, Renderer* r);
	static std::vector<Shape*> add_polyline(DxfEntity* e, Renderer* r, std::string name);
	static Shape* add_arc(glm::vec2 p1, glm::vec2 p2, float bulge, DxfEntity* e, Renderer* r, std::string name);
public:
	//static void callback(void (*func)(int count)) { _callback = func; }
	static void read(std::string path, Document* document);
};