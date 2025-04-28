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

#include "logger.h"
#include "date.h"
#include "environment.h"
#include <filesystem>

std::string Logger::_path;
std::queue<std::string> Logger::_queue;
std::mutex Logger::_mutex;
std::filebuf Logger::_file;
bool Logger::_exit;
std::thread* Logger::_thread;
std::string Logger::_trace;
bool Logger::_always_flush = false;

void Logger::log(std::string data)
{
	if (_always_flush) // debug purpose
	{
		std::ostream os(&_file);
		os << date::format("%F %T", std::chrono::system_clock::now()) << ": " << data << std::endl;
		os.flush();
	}
	else
	{
		_mutex.lock();
		_queue.push(data);
		_mutex.unlock();
	}
}

void Logger::error(std::string data)
{
	log("[ERROR]: " + data);
}

void Logger::success(std::string data)
{
	log("[SUCCESS]: " + data);
}

void Logger::warning(std::string data)
{
	log("[WARNING]: " + data);
}

void Logger::flush()
{
	while (!_queue.empty());
}

void Logger::clear()
{
	stop();
	std::filesystem::remove(_path);
	start(_path);
}

void Logger::loop()
{
	std::ostream os(&_file);
	os << date::format("%F %T", std::chrono::system_clock::now()) << ": " << "--------------- START ----------------\n";

	while (!_exit)
	{
		try {
			while (!_queue.empty())
			{
				// pick from queue
				_mutex.lock();
				std::string data = _queue.front();
				_queue.pop();
				_mutex.unlock();

				// write to file
				os << date::format("%F %T", std::chrono::system_clock::now()) << ": " << data << std::endl;
			}
			os.flush();
		}
		catch (int) {
			_mutex.unlock();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
	}

	while (!_queue.empty())
	{
		try {
			// pick from queue
			_mutex.lock();
			std::string data = _queue.front();
			_queue.pop();
			_mutex.unlock();

			// write to file
			os << date::format("%F %T", std::chrono::system_clock::now()) << ": " << data << std::endl;
		}
		catch (int) {
			_mutex.unlock();
		}
	}
	
	os << date::format("%F %T", std::chrono::system_clock::now()) << ": " << "---------------- END -----------------\n";
	
	_file.close();
}

void Logger::start(std::string path, bool always_flush)
{
	_always_flush = always_flush;

	_exit = false;
	if (path == "")
	{
		path = "log.txt";
	}
	else
	{
		// check if folder exists
		std::string folder = path.substr(0, path.find_last_of(PATH_SEPARATOR));
		std::filesystem::create_directory(folder);
	}

	_path = path;

	_file.open(path, std::ios::out | std::ios::app);

	_thread = new std::thread(&loop);
}


void Logger::stop()
{
	_exit = true;
	_thread->join();
}
