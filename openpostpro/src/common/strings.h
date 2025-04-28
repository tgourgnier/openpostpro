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
* Extensions for std::string manipulation
*************************************************************************/


#pragma once
#ifndef STRINGS_H
#define STRINGS_H

#include <string>
#include <vector>

namespace stringex
{
//public:
	/// <summary>
	/// Check if a string starts with a substring
	/// </summary>
	/// <param name="source">string to test</param>
	/// <param name="comp">pattern to find</param>
	/// <returns></returns>
	bool start_with(std::string& source, std::string comp);

	/// <summary>
	/// Check if a string ends with a substring
	/// </summary>
	/// <param name="source">string to test</param>
	/// <param name="comp">pattern to find</param>
	/// <returns></returns>
	bool end_with(std::string& source, std::string comp);
	
	/// <summary>
	/// Replace the first substring occurence with another string inside a source string
	/// </summary>
	/// <param name="str">source</param>
	/// <param name="replace">string to look for</param>
	/// <param name="with">string to paste</param>
	/// <returns></returns>
	std::string replace_string(std::string& str, const std::string replace, const std::string with);

	/// <summary>
	/// Replace every substring occurence with another string inside a source string
	/// </summary>
	/// <param name="str">source</param>
	/// <param name="replace">string to look for</param>
	/// <param name="with">string to paste</param>
	/// <returns></returns>
	/// <returns></returns>
	std::string replace_string_all(std::string& str, const std::string replace, const std::string with);
	std::string replace(std::string str, const std::string from, const std::string to);

	/// <summary>
	/// Concat an arry of strings into one string
	/// </summary>
	/// <param name="values">array of strings</param>
	/// <param name="separator">optional : string separator</param>
	/// <returns></returns>
	std::string concat_strings(std::vector<std::string>& values, std::string separator = "");

	/// <summary>
	/// Return left substring before character
	/// </summary>
	/// <param name="source">string to split</param>
	/// <param name="c">character</param>
	/// <returns></returns>
	std::string left(std::string& source, char c);

	/// <summary>
	/// Return left substring after character
	/// </summary>
	/// <param name="source">string to split</param>
	/// <param name="c">character</param>
	/// <returns></returns>
	std::string right(std::string& source, char c);

	/// <summary>
	/// Split a string before and after a character into several strings
	/// </summary>
	/// <param name="source">string to split</param>
	/// <param name="c">character</param>
	/// <returns></returns>
	std::vector<std::string> split(std::string& source, char c);

	/// <summary>
	/// Left space charater trim
	/// </summary>
	/// <param name="s">string to trim</param>
	/// <returns>trimmed string</returns>
	std::string ltrim(std::string& s);

	/// <summary>
	/// Right space charater trim
	/// </summary>
	/// <param name="s">string to trim</param>
	/// <returns>trimmed string</returns>
	std::string rtrim(std::string& s);

	/// <summary>
	/// Left & right space charater trim
	/// </summary>
	/// <param name="s">string to trim</param>
	/// <returns>trimmed string</returns>
	std::string trim(std::string& s);

	std::string to_lower(std::string s);

	std::string to_upper(std::string s);

	std::string from_escape(std::string s);

	std::string to_escape(std::string s);

	std::string to_string(float value);

	std::string to_string(double value);


#ifdef _WIN32
	/// <summary>
	/// Convert a wide char U16 into std::string
	/// </summary>
	/// <param name="input">wide char string</param>
	/// <returns>converted string</returns>
	std::string to_string(wchar_t* input);

	/// <summary>
	/// Convert an std::string to wide char string
	/// </summary>
	/// <param name="input">string to convert</param>
	/// <returns>converted string</returns>
	std::wstring to_wide_char(std::string input);
#endif
};

#endif