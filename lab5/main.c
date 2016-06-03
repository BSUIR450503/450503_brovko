#include "lib.h"

int main()
{
	HANDLE writerHandler, readerHandler;

#ifdef linux	

	pthread_create(&writerHandler, NULL, &thread_write, NULL);
	pthread_create(&readerHandler, NULL, &thread_read, NULL);
	pthread_join(writerHandler, NULL);
	pthread_join(readerHandler, NULL);

#elif _WIN32

	CONST HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONST HANDLE mutex = CreateMutex(NULL, FALSE, NULL);
	readerHandler = CreateThread(NULL, 0, &reader, mutex, 0, NULL);
	writerHandler = CreateThread(NULL, 0, &writer, mutex, 0, NULL);
	WaitForSingleObject(readerHandler, INFINITE);
	_getch();
	CloseHandle(mutex);
	ExitProcess(0);
#endif  
	return 0;
}

