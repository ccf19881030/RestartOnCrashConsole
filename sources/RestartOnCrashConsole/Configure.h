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

	// ��ȡӦ�ó����б�
	bool getAppList(AppRow& appList);
private:
	std::string m_xmlConfigPath;	// �����ļ�����·��
	static std::mutex m_mutex;
};

