#pragma once

//#include <iomanip>

#ifdef _WIN32
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <string>

#define _CRT_SECURE_NO_WARNINGS
#define HANDLE_PID Process
#define SLEEP_TIME 70

using std::cout;
using std::cin;
using std::endl;
#endif


#ifdef __linux__
#include <sys/types.h>
#include <signal.h>
#include <iostream>
#include <stdio.h>
#include <curses.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string>
#include <string.h>
#include <stdlib.h>

#define Sleep tempSleep
#define getch_noblock getchar
#define HANDLE_PID pid_t
#define SLEEP_TIME 70000

void tempSleep(int);
using std::cout;
using std::cin;
using std::endl;

#endif

static const char * processes[] = { "1. First process \r\n", "2. Second process \r\n", "3. Third process \r\n",
                                    "4. Fourth process\r\n", "5. Fifth process\r\n", "6. Sixth process\r\n",
	                            	"7. Seventh process\r\n", "8. Eighth process\r\n", "9. Ninth process\r\n",
	                            	"10. Tenth process\r\n" };

#define MAX_COUNT 10
#define RADIX 10

void print(int);
