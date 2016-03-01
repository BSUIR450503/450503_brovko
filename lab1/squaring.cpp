/* Child process
   Reads number from existing pipe and writes number^2 to pipe.
   This one is required when you use Windows */

#include <iostream>
#include <fstream>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
using namespace std;

int main(int argc, char* argv[])
{
	HANDLE pid;
	LPTSTR pipeName = TEXT("\\\\.\\pipe\\MyPipe");
	int buf;
	DWORD bytesRead = sizeof(int);
	DWORD bytesWrite = sizeof(int);

	pid = CreateFile(pipeName,GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	ReadFile(pid, &buf, sizeof(int), &bytesRead, NULL);
	buf *= buf;
	WriteFile(pid, &buf, sizeof(int), &bytesWrite, NULL);
	CloseHandle(pid);
	return 0;
}
