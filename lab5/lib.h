#pragma once

#ifdef linux
#include <stdlib.h>
#include <stdio.h>
#include <aio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>

#define TRUE 1
#define FALSE 0
#define HANDLE pthread_t
extern int8_t toggle;
extern int count;
extern struct aiocb cb;
extern char buffer[256];

void* thread_write(void* args);
void* thread_read(void* args);
#endif



#ifdef _WIN32

#ifdef USE_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif

#include <stdio.h>
#include <windows.h>
#include <conio.h>
#define SIZE 100
extern DLL_EXPORT char file_readed[5];
extern DLL_EXPORT char* buffer;
extern DLL_EXPORT char bytes_written;
DLL_EXPORT DWORD WINAPI reader(CONST LPVOID lpParam);
DLL_EXPORT DWORD WINAPI writer(CONST LPVOID lpParam);
#endif

