#pragma once
#define PUGIXML_HEADER_ONLY
#include "xml/pugixml.hpp"

#include "pub.h"

#include <mutex>

class Configure
{
public:
	Configure();
	~Configure();

	// 获取应用程序列表
	bool getAppList(AppRow& appList);
private:
	std::string m_xmlConfigPath;	// 配置文件所在路径
	static std::mutex m_mutex;
};

