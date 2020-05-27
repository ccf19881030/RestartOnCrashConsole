#include "pch.h"

#include "Configure.h"

std::mutex Configure::m_mutex;

Configure::Configure()
{
	m_xmlConfigPath = "./Configure.xml";
}

Configure::~Configure()
{

}

// ��ȡӦ�ó����б�
bool Configure::getAppList(AppRow& appList)
{
	std::lock_guard<std::mutex> locker(m_mutex);

	pugi::xml_document doc;
	// ��ȡxml�����ļ�
	pugi::xml_parse_result rc = doc.load_file(m_xmlConfigPath.c_str());
	if (rc.status == pugi::status_ok)
	{
		auto appConf = doc.child("ConfigEntity").child("Apps");
		for (auto appIter = appConf.child("App"); appIter; appIter = appIter.next_sibling("App"))
		{
			// ��ȡӦ�ó�����Ϣ
			AppItem appItem;
			// <App name = "Hubei212Recv" path = "..\Hubei212Recv\Hubei212Recv.exe" isRun = "false" waitTime = "1" / >
			appItem.appName = appIter.attribute("name").value();
			appItem.appPath = appIter.attribute("path").value();
			appItem.isRun = appIter.attribute("isRun").as_bool(true);
			appItem.waitTime = appIter.attribute("waitTime").as_uint(1);

			appList.push_back(appItem);
		}

		return true;
	}
	else if (rc.status == pugi::status_file_not_found)
	{
		printf("û�м�⵽�����ļ�,���½������ļ�. %s", rc.description());

		return false;
	}
	else
	{
		printf("�����ļ����ڴ�����������. %s", rc.description());

		return false;
	}

	return false;
}