// RestartOnCrashConsole.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

#include "DateFormatter.h"
#include "ProgressHelper.h"
#include "Configure.h"
#include "Tools.h"

#include <thread>

// 控制线程是否运行的全局变量
volatile bool run_ = false;

// 监控线程处理函数
void monitorThreadFunc()
{
	run_ = true;

	while (run_)
	{
		if (!run_) break;

		// 每隔15秒检测需要启动的进程是否正在运行，若不再运行则重新启动它
		Configure conf;
		AppRow appList;
		// 从xml配置文件中获取所有的应用程序列表信息
		conf.getAppList(appList);

		// 遍历应用程序列表
		for (auto appIter = appList.begin(); appIter != appList.end(); ++appIter)
		{
			std::string strAppExeName = appIter->appName;
			// 如果应用程序名称中不包含后缀.exe，则添加上
			if (strAppExeName.find(".exe") == std::string::npos)
			{
				strAppExeName += ".exe";
			}
			// 将应用程序的相对路径转换成绝对路径
			std::string strFullPath = Tools::Files::abs_path(appIter->appPath);
			// 启动需要启动的进程
			if (appIter->isRun)
			{
				// 如果需要启动的应用程序处于未运行状态，则启动它
				if (!ProgressHelper::isExeRunning(strAppExeName.c_str()))
				{
					// 注意：这里调用ShellExecute启动外部应用程序,使用全路径(包括应用程序名称和扩展名.exe)
					ProgressHelper::StartProgress2(strFullPath.c_str());
					// 休眠waitTime秒
					ssleep(appIter->waitTime);
				}
			}
		}

		// 休眠15秒
		sleep_if(run_, 15);
	}
}

int main(int argc, char* argv[])
{
    // 启动后台监控线程，用于监控需要启动的进程
	std::thread thr = std::thread(monitorThreadFunc);
	
	// 等待用户按下任意键，退出程序
	getchar();

	// 退出后台监控进程
	run_ = false;
	
	// 等待后台监控子线程退出
	if (thr.joinable()) {
		thr.join();
	}

	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
