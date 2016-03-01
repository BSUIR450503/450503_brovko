#ifdef _WIN32
#include <fstream>
#include "windows.h"
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include<iostream>
using namespace std;
#define PID HANDLE
#define createProcess() createWindowsProcess()
#endif


#ifdef __linux__
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<iostream>
using namespace std;
#define PID pid_t
#define createProcess() createLinuxProcess()
#endif


class myProcess
{
public:

void createWindowsProcess();
void createLinuxProcess();

};

#ifdef __linux__
void myProcess::createLinuxProcess()
{
   int fd[2], status;
   PID pid;
   char  resString[14];

   if(pipe(fd) < 0)
   {
     cout << "Can't open pipen" << endl;
     exit(-1);
   }

   pid = fork();

   if(pid < 0)
   {
      cout << "Can't fork childn" << endl;
      exit(-1);
   }

   else if (pid > 0)     /* Parent process */
   {

      char temp[14];
      cout << "enter"<<endl;
      cin >> temp;
      write(fd[1], temp, 14);

      wait(&status);

      read(fd[0], resString, 14);
      cout << "Parent, result: " << resString <<endl;
      close(fd[1]);
      close(fd[0]);
   }

   else                  /* Child process */
   {
      int buf;
      read(fd[0], resString, 14);
      sscanf(resString, "%d", &buf);
      buf*=buf;
      sprintf(resString, "%d", buf);
      write(fd[1], resString, 14);
    }
}
#endif

#ifdef _WIN32
void myProcess::createWindowsProcess()
{
	STARTUPINFO startupInfo;
	ZeroMemory(&startupInfo, sizeof(STARTUPINFO));
	PROCESS_INFORMATION procInfo;
	DWORD dwExitCode;

	HANDLE pid;
	LPTSTR pipeName = TEXT("\\\\.\\pipe\\MyPipe");
	int buf;
	DWORD bytesRead = sizeof(int);
	DWORD bytesWrite = sizeof(int);

	pid = CreateNamedPipe(pipeName, PIPE_ACCESS_DUPLEX, PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
	      1, 1024 * 8, 1024 * 8, NMPWAIT_USE_DEFAULT_WAIT, NULL);

	if (pid == INVALID_HANDLE_VALUE)
	{
		cout << "Cannot create a pipe. Code:" << (int)GetLastError() << endl;
		exit(-1);
	}

	if (!CreateProcess(L"E:\\visual\\spo lab1\\Debug\\squaring.exe",
                                                                   NULL,
                                                                   NULL,
                                                                   NULL,
                                                                   FALSE,
                                                                   NULL,
                                                                   NULL,
                                                                   NULL,
                                                                   &startupInfo,
                                                                   &procInfo))
   	{
		cout << "Cannot create a process. Code:" << (int)GetLastError() << endl;
		exit(-2);
	}

	if (!ConnectNamedPipe(pid, NULL))
	{
		cout << "Cannot connect a pipe. Code:" << (int)GetLastError() << endl;
		exit(-3);
	}

	cout << "Enter number" << endl;
	cin >> buf;
	WriteFile(pid, &buf, sizeof(int), &bytesWrite, NULL);
	WaitForSingleObject(procInfo.hProcess, INFINITE);
	ReadFile(pid, &buf, sizeof(int), &bytesRead, NULL);

	cout << "Result is " << buf << endl;

	CloseHandle(pid);
	CloseHandle(procInfo.hThread);
	CloseHandle(procInfo.hProcess);

	system("pause");
}
#endif

