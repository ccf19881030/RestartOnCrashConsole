#pragma once

#include <string>
#include <direct.h>
#include <stdlib.h>
#include  <limits.h>
#ifdef _WIN32
#include <windows.h>
#include <direct.h>
#include <io.h>
#else
#include<unistd.h>
#endif

namespace Tools
{
	class Files
	{
	public:
		static  std::string abs_path(std::string path)
		{
#ifdef _WIN32
#define max_path 4096
			char resolved_path[max_path] = { 0 };
			_fullpath(resolved_path, path.c_str(), max_path);
#else
			//linux release有个坑，需要大点的空间
#define max_path 40960
			char resolved_path[max_path] = { 0 };
			realpath(path.c_str(), resolved_path);
#endif
			return std::string(resolved_path);
		}
	};
}