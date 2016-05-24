#ifdef __linux__
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/sem.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <syscall.h>
#include <string.h>
#include <ncurses.h>
#define TRUE 1
#define FALSE 0
#define THREADS_NUMBER 10
#define SLEEP_TIME 100000
#endif


#ifdef _WIN32
#include <windows.h>
#include <stdio.h>
#define SLEEP_TIME 60
#endif