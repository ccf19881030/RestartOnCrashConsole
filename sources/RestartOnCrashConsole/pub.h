#pragma once

#include <string>
#include <vector>
#include <map>

struct AppItem
{
	std::string appName;			// Ӧ�ó�������
	std::string appPath;			// �ػ��������·��
	bool isRun;						// �Ƿ���Ҫ������������������Ϊtrue������Ϊfalse
	unsigned int waitTime;			// ��ǰ����������ȴ�ʱ�䣬��redis������ȴ�����ִ����һ����
};

typedef std::vector<AppItem> AppRow;
typedef std::map<std::string, AppRow> AppMap;
