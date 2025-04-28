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
* Read/write into a standard ini file with [SECTIONS] and key=value lines
* Default ini file is located in 
* 'home\.executable_name_folder\executable_name.ini'
*************************************************************************/


#pragma once
#ifndef INIFILE_H
#define INIFILE_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>


class IniFile
{
private:
	std::string _path;
	std::vector<std::string> _lines;

	int findSection(std::string section);
	int findName(std::string name, int offset);

public:
	IniFile(std::string path="");
	~IniFile();

	std::string path() { return _path; }
	
	void write();

	void set(std::string section, std::string name, char const* value);
	void set(std::string section, std::string name, std::string value);
	void set(std::string section, std::string name, int value);
	void set(std::string section, std::string name, float value);
	void set(std::string section, std::string name, double value);
	void set(std::string section, std::string name, bool value);

	std::string get_string(std::string section, std::string name, std::string def = "");
	int get_int(std::string section, std::string name, int def = 0);
	float get_float(std::string section, std::string name, float def = 0);
	double get_double(std::string section, std::string name, double def = 0);
	bool get_bool(std::string section, std::string name, bool def = false);

	void remove(std::string section, std::string name);
	void remove_section(std::string section);

	/// <summary>
	/// Return the whole file content
	/// </summary>
	/// <returns></returns>
	std::string read_data();

	/// <summary>
	/// Return the whole file content
	/// </summary>
	/// <returns></returns>
	std::vector<std::string> get_data();

	/// <summary>
	/// Use data as input
	/// </summary>
	/// <param name="data"></param>
	void load_data(std::string data);
	
	/// <summary>
	/// Use data as input
	/// </summary>
	/// <param name="data"></param>
	void load_data(std::vector<std::string> data);
};

#endif