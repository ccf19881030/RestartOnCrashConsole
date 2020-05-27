#pragma once

#include <Windows.h>
#include <Tlhelp32.h>
#include<comdef.h>

// ���̴�����
class ProgressHelper
{
public:
	// �ж�ָ���������Ľ����Ƿ����
	// �ж�ĳ�������Ƿ���������
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

	// ���ݽ�����(��NotePad.exe)��ȡ����ID
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
			//�Ƚ������ַ���������ҵ���Ҫ�ҵĽ���
			if (strcmp(pname, processName) == 0)
			{
				id = pe.th32ProcessID;
				break;
			}

		} while (true);

		CloseHandle(hSnapshot);

		return id;
	}


	// ���ݳ������ر�ĳ������
	static void KillProgress(const char* exeName)
	{
		//ͨ����������ȡ����ID
		// ����test.exe
		/*
			ע�⣺
			�������ȡ����ID��ʱ��һ����"test.exe",ֻ��exe��������֣�û��·����û��·����û��·����
			��Ҫ������˵���飡�����ȡ��������ID��
			����WinExec�򿪵�ʱ���Ҫ����·���ˣ���Ȼ������Ƴ����exe��������ͬĿ¼�£��Ͳ�������
		*/
		DWORD pid = GetProcessIdFromName(exeName);
		//��ȡ���̵����Ȩ��
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
		//�رս���
		TerminateProcess(hProcess, 0);
		CloseHandle(hProcess);
	}

	// ����WinExec����
	static void StartProgress1(const char* fullPath)
	{
		// WinExec("C:\\exams\\test.exe", SW_SHOW);
		WinExec(fullPath, SW_SHOW);
	}

	// ����ĳ���ⲿ����
	// ��Ҫ�ṩ����·��
	// ��xml�����ļ��е�APP�����·��������Ҫת���ɾ���·��
	static void StartProgress2(const char* fullPath)
	{
		ShellExecute(NULL, "open", fullPath, NULL, NULL, SW_SHOW);
	}

	// ʹ��CreateProcess����ĳ���ⲿ����
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
			printf("����ʧ�ܵĽ���ȫ·��Ϊ��%s\n", fullPath);
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