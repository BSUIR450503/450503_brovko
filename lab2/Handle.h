#pragma once

#include "lib.h"
#include "processAct.h"

class Handle
{
	char key;
	int numOfProcess;
	HANDLE_PID process[MAX_COUNT];
public:
	Handle()
	{
		numOfProcess = 0;
	}
	void run(int, char**);
	void print(int numberOfProcess);
};


void Handle::print(int numberOfProcess)
{
	for (int i = 0; i < strlen(processes[numberOfProcess - 1]); i++)
	{
		cout << processes[numberOfProcess - 1][i];
		Sleep(SLEEP_TIME);
	}

	return;
}


void Handle::run(int argNum, char **argv)
{
	if (argNum == 2)
	{
#ifdef _WIN32
		char toClose[RADIX];
		strcpy(toClose, argv[1]);
		strcat(toClose, argv[1]);

		HANDLE canPrintEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, argv[1]);
		HANDLE canCloseEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, toClose);

		while (1)
		{
			if (WaitForSingleObject(canPrintEvent, 1) == WAIT_OBJECT_0)
			{
				print(atoi(argv[1]));
				ResetEvent(canPrintEvent);
			}
			if (WaitForSingleObject(canCloseEvent, 0) == WAIT_OBJECT_0)
			{
				CloseHandle(canCloseEvent);
				CloseHandle(canPrintEvent);
				return;
			}
		}
#endif
	} 
	else
	{

#ifdef _WIN32

		int currentNum = 1;
		system("cls");

		while (1)
		{
			key = getch_noblock();
			Sleep(1000);
			switch (key)
			{
				case '+':
				{
					if (numOfProcess < MAX_COUNT)
					{
						numOfProcess++;
						process[numOfProcess - 1].createNewProcess(value[0], numOfProcess);
					}
					break;
				}
				case '-':
				{
					if (numOfProcess > 0)
					{
						SetEvent(process[--numOfProcess].getCloseEvent());
					}
					break;
				}
				case 'q':
				{
					if (numOfProcess > 0)
					{
						for (int i = 0; i < numOfProcess; i++)
						{
							SetEvent(process[i].getCloseEvent());
						}
					}
					return;
				}
			}
			if (numOfProcess > 0 && WaitForSingleObject(process[currentNum - 1].getPrintEvent(), 0) == WAIT_TIMEOUT)
			{
				if (currentNum >= numOfProcess)
				{
					currentNum = 1;
				}
				else
				{
						currentNum++;
				}
				SetEvent(process[currentNum - 1].getPrintEvent());
			}
		}

#elif __linux__

		int currentNum = 0;
	
		initscr();
		clear();
		noecho();
		refresh();

		printSignal.sa_handler = setPrintFlag;
		sigaction(SIGUSR1, &printSignal, NULL);

		endSignal.sa_handler = setEndFlag;
		sigaction(SIGUSR2, &endSignal, NULL);

		while (1)
		{
			key = getch_noblock();
	
			Sleep(1000);
			switch (key)
			{
				case '+':
				{
					if (numOfProcess < MAX_COUNT)
					{
						process[numOfProcess] = fork();
						numOfProcess++;
	
						switch (process[numOfProcess - 1])
						{
							case 0:
							{
								endFlag = 0;
								while (!endFlag)
								{
									Sleep(1000);
									if (printFlag)
									{
										print(numOfProcess);
										refresh();
										printFlag = 0;
										kill(getppid(), SIGUSR2);
									}
								}
								return;
								break;
							}
							case -1:
							{
								cout << "CreateProcess failed!" << endl;
								break;
							}
							default:
							{
								break;
							}
						}
					}
					break;
				}
	
				case '-':
				{
					if (numOfProcess > 0)
					{
						kill(process[numOfProcess - 1], SIGUSR2);
						waitpid(process[numOfProcess - 1], NULL, 0);
						kill(process[numOfProcess - 1], SIGKILL);
						waitpid(process[numOfProcess - 1], NULL, 0);
						numOfProcess--;
					}
					break;
				}

				case 'q':
				{
					if (numOfProcess > 0)
					{
						for (; numOfProcess > 0; numOfProcess--) 
						{
							kill(process[numOfProcess - 1], SIGUSR2);
							waitpid(process[numOfProcess - 1], NULL, 0);
							kill(process[numOfProcess - 1], SIGKILL);
							waitpid(process[numOfProcess - 1], NULL, 0);							
						}
					}
					clear();
					endwin();
					return;
				}
			}
			if (endFlag && numOfProcess > 0)
			{
				endFlag = 0;
				if (currentNum >= numOfProcess - 1)
				{
					currentNum = 0;
				}
				else
				{
						currentNum++;
				}
				kill(process[currentNum], SIGUSR1);
			}
			refresh();
		}

#endif
			}

}