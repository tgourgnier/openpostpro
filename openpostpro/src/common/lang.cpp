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

#include "lang.h"
#include "environment.h"
#include <filesystem>
#include <fstream>
#include <strings.h>

#ifdef _WIN32
#define _NEW_LINE "\r\n"
#define _NL_LENGTH 2
#else
#define _NEW_LINE "\n"
#define _NL_LENGTH 1
#endif

std::map<std::string, std::string> Lang::m_lang;
std::string Lang::m_name;

std::vector<std::string> Lang::get_langs_files(std::string path)
{
	std::filesystem::path folder(environment::application_path());
	folder /= "lang";

	if (std::filesystem::exists(path))
	{
		folder = path;
	}

	std::vector<std::string> result;

	for (const auto& entry : std::filesystem::directory_iterator(folder))
	{
		if (entry.is_regular_file())
		{
			auto extension = entry.path().extension().string();
			if (extension == ".txt")
			{
				result.push_back(entry.path().string());
			}
		}
	}

	return result;
}

std::vector<std::string> Lang::get_langs(std::string path)
{
	std::filesystem::path folder(environment::application_path());
	folder /= "lang";

	if (std::filesystem::exists(path))
	{
		folder = path;
	}

	std::vector<std::string> result;

	for (const auto& entry : std::filesystem::directory_iterator(folder))
	{
		if (entry.is_regular_file())
		{
			auto extension = entry.path().extension().string();
			if (extension == ".txt")
			{
				auto filename = entry.path().filename().string();
				result.push_back(filename.substr(0, filename.length()-4));
			}
		}
	}

	return result;
}

std::map<std::string, std::string> Lang::get_lang(std::string name, std::string path)
{
	std::map<std::string, std::string> result;

	std::string filename = path;

	if (!std::filesystem::exists(path))
	{
		filename = environment::combine_path(environment::combine_path(environment::application_path(),"lang"), name) + ".txt";
	}

	std::ifstream input(filename);
	for (std::string line; std::getline(input, line); ) {
		auto index = line.find_first_of('=');
		if (index > 0)
		{
			auto code = line.substr(0, index);
			auto content = line.substr(index + 1);

			// replace "{\n}" with new line
			std::size_t pos = 0;
			while ((pos = content.find("{\n}", pos)) != std::string::npos) {
				content.replace(pos, 4, _NEW_LINE);
				pos += _NL_LENGTH;
			}

			result[code] = stringex::from_escape(content);
		}
	}

	return result;
}

void Lang::load(std::string name, std::string path)
{
	m_name = name;
	Lang::m_lang = get_lang(name, path);
}

const char* Lang::l(std::string code)
{
	if (Lang::m_lang.find(code) == m_lang.end())
	{
		Lang::m_lang[code] = code;
	}
	return Lang::m_lang[code].c_str();
}

std::string Lang::t(std::string code)
{
	if (Lang::m_lang.find(code) == m_lang.end())
	{
		Lang::m_lang[code] = code;
	}
	return Lang::m_lang[code];
}