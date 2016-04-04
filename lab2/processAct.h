#pragma once
#include "lib.h"

#ifdef __linux__

bool printFlag = false;
bool endFlag = true;

struct sigaction printSignal;
struct sigaction endSignal;

void setPrintFlag(int signal)
{
  printFlag = true;
}

void setEndFlag(int signal)
{
  endFlag = true;
}

void tempSleep(int slpTime)
{
	usleep(slpTime);
	fflush(stdout);
	refresh();
}
#endif



#ifdef _WIN32

class Process
{
private:
	PROCESS_INFORMATION processInfo;
	HANDLE printEvent;
	HANDLE closeEvent;
public:
	PROCESS_INFORMATION createNewProcess(char*, int);
	HANDLE getPrintEvent();
	HANDLE getCloseEvent();
};

PROCESS_INFORMATION Process::createNewProcess(char *path, int processNumber)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	char procNum[RADIX];
	char toClose[RADIX];
	char command[RADIX] = "-n ";

	_itoa(processNumber, procNum, RADIX);
	strcat(command, procNum);

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	if (!CreateProcess(path, command, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi))
	{
		cout << "CreateProcess failed. Error code: " << (int)GetLastError() << endl;
		exit((int)GetLastError());
	}

	strcpy(toClose, procNum);
	strcat(toClose, procNum);

	// closeEvent auto-resets
	closeEvent = CreateEvent(NULL, FALSE, FALSE, toClose);
	// printEvent resets by user
	printEvent = CreateEvent(NULL, TRUE, FALSE, procNum);

	return pi;
}

HANDLE Process::getPrintEvent()
{
	return printEvent;
}

HANDLE Process::getCloseEvent()
{
	return closeEvent;
}

int getch_noblock()
{
	if (_kbhit())
		return _getch();
	else
		return -1;
}

#endif