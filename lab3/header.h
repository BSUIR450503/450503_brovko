#ifdef __linux__
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/select.h>
#include <termios.h>
#include <stropts.h>
#define TRUE 1
#define FALSE 0
#endif


#ifdef _WIN32
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <atlbase.h>
#include <atlconv.h>
#include <Windows.h>
#pragma comment(lib, "user32.lib")
#define BUF_SIZE 256
#define SIZE 256
#define SLEEP_TIME 100000
#endif