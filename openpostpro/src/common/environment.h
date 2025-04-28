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
* methods to manage environment data
* Application path
* User path
*************************************************************************/

#pragma once
#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <string>
#include <map>

#ifdef _WIN32
#define PATH_SEPARATOR '\\'
#else
#define PATH_SEPARATOR '/'
#endif

namespace environment
{
	std::string current_path();

	std::string application_full_path();

	std::string application_path();

	std::string application_name();

	std::string application_name_without_extension();

	std::string user_path();

	std::string user_documents();

	std::string application_data_path();

	void init();

	std::string combine_path(std::string left, std::string right);


	struct FontFamily
	{
		std::string name;
		std::string regular_path;
		std::string italic_path;
		std::string bold_path;
		std::string bold_italic_path;
	};

	std::map<std::string, FontFamily> fonts();

	static unsigned int _next_id = 1;
	unsigned int next_id();
	unsigned int next_id(unsigned int id);

	std::tm local_time(time_t timer);

	const std::string current_date_time();
};

#endif