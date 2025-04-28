#include "file.h"

#include <iostream>
#include <fstream>
#include <filesystem>

#ifndef _WIN32
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

namespace file
{
	void write_all_text(std::string path, std::string text)
	{
		std::filebuf file;

		file.open(path, std::ios::out);
		std::ostream os(&file);
		os << text;
		file.close();
	}

	void write_all_lines(std::string path, std::vector<std::string> lines)
	{
		if (lines.size() == 0) return;

		std::string buffer("");
		std::string last = lines.back();
		lines.pop_back();

		for (std::string line : lines)
		{
			buffer += line + "\n";
		}

		buffer += last;

		write_all_text(path, buffer);
	}

	std::vector<std::string> read_all_lines(std::string path)
	{
		std::vector<std::string> result;
		if (std::filesystem::exists(path))
		{
			std::string line;
			std::ifstream input(path);
			if (std::getline(input, line))
			{
				// check if utf8
				if (line.size() > 3 && line[0] == '\xef' && line[1] == '\xbb' && line[2] == '\xbf')
					result.push_back(line.substr(3));
				else
					result.push_back(line);
			}
			while (std::getline(input, line))
			{
				result.push_back(line);
			}
		}

		return result;
	}

	std::string read_all_text(std::string path)
	{
		if (std::filesystem::exists(path))
		{
			auto size = std::filesystem::file_size(path);

			std::ifstream ifs(path);
			std::string content;
			content.reserve(size);
			content.assign((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

			if (content.size() > 3 && content[0] == '\xef' && content[1] == '\xbb' && content[2] == '\xbf')
				return content.substr(3);

			return content;
		}
		else
			return "";
	}
}