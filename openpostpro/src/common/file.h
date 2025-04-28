/******************************************************************
* OpenPostPro - www.openpostpro.org
* ------------------------------------------------------------------------
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
* methods to read/write text files in a single line
*************************************************************************/

#pragma once
#ifndef _FILE_H
#define _FILE_H

#include <string>
#include <vector>

namespace file
{
	void write_all_text(std::string path, std::string text);

	void write_all_lines(std::string path, std::vector<std::string> lines);

	std::vector<std::string> read_all_lines(std::string path);

	std::string read_all_text(std::string path);
};

#endif