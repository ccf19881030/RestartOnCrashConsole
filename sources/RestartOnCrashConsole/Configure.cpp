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

// 获取应用程序列表
bool Configure::getAppList(AppRow& appList)
{
	std::lock_guard<std::mutex> locker(m_mutex);

	pugi::xml_document doc;
	// 读取xml配置文件
	pugi::xml_parse_result rc = doc.load_file(m_xmlConfigPath.c_str());
	if (rc.status == pugi::status_ok)
	{
		auto appConf = doc.child("ConfigEntity").child("Apps");
		for (auto appIter = appConf.child("App"); appIter; appIter = appIter.next_sibling("App"))
		{
			// 获取应用程序信息
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
		printf("没有检测到配置文件,请新建配置文件. %s", rc.description());

		return false;
	}
	else
	{
		printf("配置文件存在错误，请检查配置. %s", rc.description());

		return false;
	}

	return false;
}