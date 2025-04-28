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
* Log strings into a text file using a dedicated thread
*************************************************************************/

#pragma once
#ifndef _LOGGER_H
#define _LOGGER_H

#include <string>
#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <fstream>

class Logger
{
private:
	static std::string _path;
	static std::queue<std::string> _queue;
	static std::mutex _mutex;
	static std::filebuf _file;
	static std::thread* _thread;
	static std::string _trace;
	static bool _exit;
	static bool _always_flush;

private:
	/// <summary>
	/// Thread loop
	/// </summary>
	static void loop();

public:
	/// <summary>
	/// Log file path
	/// </summary>
	static std::string path() { return _path; }

	/// <summary>
	/// Start logging
	/// <param name="path">optional log file path, default is log.txt in the executable folder</param>
	/// </summary>
	static void start(std::string path = "", bool always_flush=false);

	/// <summary>
	/// Stop logging
	/// </summary>
	static void stop();

	/// <summary>
	/// Log data string
	/// </summary>
	static void log(std::string data);

	/// <summary>
	/// Log data string
	/// </summary>
	static void error(std::string data);

	/// <summary>
	/// Log data string
	/// </summary>
	static void success(std::string data);

	/// <summary>
	/// Log data string
	/// </summary>
	static void warning(std::string data);

	/// <summary>
	/// Force file write
	/// </summary>
	static void flush();

	/// <summary>
	/// Clear log file
	/// </summary>
	static void clear();

	/// <summary>
	/// Static trace string
	/// </summary>
	static std::string trace() { return _trace; };

	/// <summary>
	/// Set the trace string
	/// </summary>
	static void trace(std::string data) { _trace = data; };
};

#endif