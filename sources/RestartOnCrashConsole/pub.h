#pragma once

#include <string>
#include <vector>
#include <map>

struct AppItem
{
	std::string appName;			// 应用程序名称
	std::string appPath;			// 守护程序相对路径
	bool isRun;						// 是否需要启动，如需启动设置为true，否则为false
	unsigned int waitTime;			// 当前程序启动后等待时间，如redis启动后等待五秒执行下一程序
};

typedef std::vector<AppItem> AppRow;
typedef std::map<std::string, AppRow> AppMap;
