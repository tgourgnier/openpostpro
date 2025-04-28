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
* Manage string resources for language. Default language files are located
* into a lang sub-folder. 
* A language file contains :
* a pair of KEY=value on a single line
* Use escape string {\n} for new line
*************************************************************************/

#pragma once
#ifndef LANG_H
#define LANG_H

#include <map>
#include <string>
#include <vector>

class Lang {
private:
	/// <summary>
	/// Store dictonnary
	/// </summary>
	static std::map<std::string, std::string> m_lang;

	/// <summary>
	/// Read input language file
	/// </summary>
	/// <param name="name">Language code</param>
	/// <param name="path">Optional : input file path</param>
	/// <returns>std::map<std::string, std::string> containing key/value pairs</returns>
	static std::map<std::string, std::string> get_lang(std::string name, std::string path = "");

	static std::string m_name;

public:
	static std::string getName() { return m_name; };

	/// <summary>
	/// Return array of languages available
	/// </summary>
	/// <param name="path"></param>
	/// <returns></returns>
	static std::vector<std::string> get_langs_files(std::string path = "");

	/// <summary>
	/// Return array of languages available
	/// </summary>
	/// <param name="path"></param>
	/// <returns></returns>
	static std::vector<std::string> get_langs(std::string path = "");

	/// <summary>
	/// Load selected current language
	/// </summary>
	/// <param name="name">Language code</param>
	/// <param name="path">Optional : input file path</param>
	static void load(std::string name, std::string path = "");;

	/// <summary>
	/// Return associated value of key
	/// </summary>
	/// <param name="code">Key code</param>
	/// <returns>const char* "value"</returns>
	static const char* l(std::string code);;

	/// <summary>
	/// Return associated value of key
	/// </summary>
	/// <param name="code">Key code</param>
	/// <returns>std::string "value"</returns>
	static std::string t(std::string code);;
};
#endif