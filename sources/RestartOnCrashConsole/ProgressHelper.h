#pragma once

#include <Windows.h>
#include <Tlhelp32.h>
#include<comdef.h>

// 进程处理类
class ProgressHelper
{
public:
	// 判断指定进程名的进程是否存在
	// 判断某个进程是否正在运行
	static bool isExeRunning(const char *pProcessName)
	{
		HANDLE hProcessSnap;
		BOOL bRet = false;

		PROCESSENTRY32 pe32;
		// Take a snapshot of all processes in the system
		hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (hProcessSnap == INVALID_HANDLE_VALUE)
		{
			bRet = false;
			return bRet;
		}
		// Set the size of the structure before using it.
		pe32.dwSize = sizeof(PROCESSENTRY32);
		// Retrieve information about the first process,
		// and exit if unsuccessful
		if (!Process32First(hProcessSnap, &pe32))
		{
			CloseHandle(hProcessSnap);
			bRet = false;
			return bRet;
		}
		// Now walk the snapshot of processes, and
		// display information about each process in turn
		while (Process32Next(hProcessSnap, &pe32))
		{
			if (strcmp(pProcessName, pe32.szExeFile) == 0)
			{
				return true;
			}
		}
		CloseHandle(hProcessSnap);

		return bRet;
	}

	// 根据进程名(如NotePad.exe)获取进程ID
	static DWORD GetProcessIdFromName(const char* processName)
	{
		PROCESSENTRY32 pe;
		DWORD id = 0;

		HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		pe.dwSize = sizeof(PROCESSENTRY32);
		if (!Process32First(hSnapshot, &pe))
			return 0;
		char pname[300];
		do
		{
			pe.dwSize = sizeof(PROCESSENTRY32);
			if (Process32Next(hSnapshot, &pe) == FALSE)
				break;
			//比较两个字符串，如果找到了要找的进程
			if (strcmp(pname, processName) == 0)
			{
				id = pe.th32ProcessID;
				break;
			}

		} while (true);

		CloseHandle(hSnapshot);

		return id;
	}


	// 根据程序名关闭某个程序
	static void KillProgress(const char* exeName)
	{
		//通过进程名获取进程ID
		// 比如test.exe
		/*
			注意：
			在上面获取进程ID的时候，一定是"test.exe",只是exe程序的名字，没有路径！没有路径！没有路径！
			重要的事情说三遍！否则获取不到进程ID。
			但是WinExec打开的时候就要加上路径了，当然如果控制程序和exe程序在相同目录下，就不必啦。
		*/
		DWORD pid = GetProcessIdFromName(exeName);
		//获取进程的最大权限
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
		//关闭进程
		TerminateProcess(hProcess, 0);
		CloseHandle(hProcess);
	}

	// 调用WinExec函数
	static void StartProgress1(const char* fullPath)
	{
		// WinExec("C:\\exams\\test.exe", SW_SHOW);
		WinExec(fullPath, SW_SHOW);
	}

	// 启动某个外部程序
	// 需要提供绝对路径
	// 若xml配置文件中的APP是相对路径，则需要转换成绝对路径
	static void StartProgress2(const char* fullPath)
	{
		ShellExecute(NULL, "open", fullPath, NULL, NULL, SW_SHOW);
	}

	// 使用CreateProcess启动某个外部进程
	static void StartProgress3(const char* fullPath)
	{
		STARTUPINFO si;
		PROCESS_INFORMATION pi;

		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		si.dwFlags = STARTF_USESHOWWINDOW;
		//si.wShowWindow = SW_SHOWMINNOACTIVE;
		si.wShowWindow = SW_SHOW;
		ZeroMemory(&pi, sizeof(pi));

		// Start the child process. 
		if (!CreateProcess(NULL,   // No module name (use command line)
			(LPSTR)fullPath,       // Command line
			NULL,           // Process handle not inheritable
			NULL,           // Thread handle not inheritable
			FALSE,          // Set handle inheritance to FALSE
			0,              // No creation flags
			NULL,           // Use parent's environment block
			NULL,           // Use parent's starting directory 
			&si,            // Pointer to STARTUPINFO structure
			&pi)           // Pointer to PROCESS_INFORMATION structure
			)
		{
			printf("CreateProcess failed (%d).\n", GetLastError());
			printf("启动失败的进程全路径为：%s\n", fullPath);
			return;
		}

		// Wait until child process exits.
		// WaitForSingleObject(pi.hProcess, INFINITE);
		WaitForSingleObject(pi.hProcess, 5);

		// Close process and thread handles. 
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
};