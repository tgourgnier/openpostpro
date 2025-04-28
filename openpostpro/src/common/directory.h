#include <string>
#include <vector>

#include <sys/types.h>
#include <sys/stat.h>

#ifdef _WIN32
#include <direct.h>
#define CreateDir(x) _mkdir(x)
#define RemoveDir(x) _rmdir(x)
#else
#include <unistd.h>
#define CreateDir(x) mkdir(x, S_IRWXU)
#define RemoveDir(x) rmdir(x)
#endif

#pragma once
class Directory
{
public:
	static bool exists(std::string path)
	{
		struct stat info;
		if (stat(path.c_str(), &info) == 0)
			if (info.st_mode & S_IFDIR)
				return true;
		
		return false;
	}

	static bool create(std::string path)
	{
		if (!exists(path))
		{
			auto names = stringex::split(path, PATH_SEPARATOR);

			if (names.size() > 1)
			{
				bool result = true;
				std::string dir = names[0];

				for (int i = 1; i < names.size(); i++)
				{
					dir = dir + PATH_SEPARATOR + names[i];
					if (!exists(dir))
						result = result && CreateDir(dir.c_str()) == 0;
				}
				return result;
			}
		}

		return false;
	}

	static bool remove(std::string path)
	{
		return RemoveDir(path.c_str()) == 0;
	}

	//static std::vector<std::string> List(std::string pattern)
	//{
	//	return std::vector<std::string>();
	//}
};




