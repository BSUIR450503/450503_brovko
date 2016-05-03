#include "header.h"

#ifdef __linux__
int main(int argc, char**argv)
{
    int file_descriptor[2];
    int pipes[2];
    
    sscanf (argv[3],"%d", file_descriptor);
    sscanf (argv[4],"%d", file_descriptor + 1);

    sscanf (argv[5],"%d", pipes);
    sscanf (argv[6],"%d", pipes + 1);
    
    sem_t* semafor = NULL;
    sem_t* semafor1 = NULL;
    semafor = sem_open(argv[2], O_CREAT, 0777, 1);
    semafor1 = sem_open(argv[1], O_CREAT, 0777, 1);
    
    char read_buffer[256];
    char write_buffer[256];  
	int child_semafor;
	int child_semafor1;
	
	close(file_descriptor[1]);
	close(pipes[0]);
	while(TRUE)
	  {

	    sem_getvalue(semafor, &child_semafor);
	    if(child_semafor == 0)
	      {
	      	sem_post(semafor);
		read(file_descriptor[0], read_buffer, sizeof(read_buffer));
		printf("The transmitted string: %s", read_buffer);

  	  	if (read_buffer[0] == '/') 
  	  	{
  	  	  	sem_close(semafor);
  		    sem_close(semafor1);
	    	  exit(0);
    	}
		sem_trywait(semafor);
	    }

	    sem_getvalue(semafor1, &child_semafor1);

	    if(child_semafor1 == 0) {
	    sem_post(semafor1);
	    printf("Enter the string\n");
	    fgets(write_buffer, sizeof(write_buffer), stdin);
		printf("Ready to transmit\n");
		write(pipes[1], write_buffer, strlen(write_buffer) + 1);
		printf("The string has been sent\n");
		sem_trywait(semafor1);
		}

	  }  
	close(file_descriptor[0]);
	close(pipes[1]); 	
	return 0;
}
#endif


#ifdef _WIN32
TCHAR szName[] = TEXT("Local\\mapfile");
TCHAR file_name[] = TEXT("Local\\mapfile1");

int main()
{
	HANDLE hMapFile;
	LPCTSTR pBuf;
	LPSTR lpszAscii = NULL;

	volatile HANDLE sem, print_sem, sem1, print_sem1;
	sem = OpenSemaphore(SYNCHRONIZE, TRUE, L"SEMAFOR");
	print_sem = CreateSemaphore(NULL, 0, 1, L"SEMAWHILE");

	sem1 = CreateSemaphore(NULL, 0, 1, L"SEMAFOR1");
	print_sem1 = OpenSemaphore(SYNCHRONIZE, TRUE, L"SEMAWHILE1");

	USES_CONVERSION;


	hMapFile = OpenFileMapping(
		FILE_MAP_ALL_ACCESS,   // read/write access
		FALSE,                 // do not inherit the name
		szName);               // name of mapping object

	if (hMapFile == NULL)
	{
		_tprintf(TEXT("Could not open file mapping object (%d).\n"),
			GetLastError());
		Sleep(10000);
		return -1;
	}

	pBuf = (LPTSTR)MapViewOfFile(hMapFile, // handle to map object
		FILE_MAP_ALL_ACCESS,  // read/write permission
		0,
		0,
		BUF_SIZE);

	if (pBuf == NULL)
	{
		_tprintf(TEXT("Could not map view of file (%d).\n"),
			GetLastError());

		CloseHandle(hMapFile);

		return -1;
	}


	TCHAR string[SIZE];
	char buffer[SIZE];
	LPCTSTR buffer_pointer;
	HANDLE file_handler;

	file_handler = CreateFileMapping(
		INVALID_HANDLE_VALUE,
		NULL,
		PAGE_READWRITE,
		0,
		SIZE,
		file_name);

	if (NULL == file_handler)
	{
		perror("CreateFileMapping");
		return -1;
	}

	hMapFile = CreateFileMapping(
		INVALID_HANDLE_VALUE,
		NULL,
		PAGE_READWRITE,
		0,
		SIZE,
		szName);

	if (NULL == hMapFile)
	{
		perror("CreateFileMapping");
		return -1;
	}

	buffer_pointer = (LPTSTR)MapViewOfFile(file_handler, FILE_MAP_ALL_ACCESS, 0, 0, SIZE);

	if (NULL == buffer_pointer)
	{
		perror("MapViewMapping");
		CloseHandle(file_handler);
		return -1;
	}

	while (TRUE)
	{

		WaitForSingleObject(print_sem1, INFINITE);
		lpszAscii = T2A((LPTSTR)pBuf);
		int len = strlen(lpszAscii);
		char something[256];
		strcpy(something, lpszAscii);
		printf("I got %s\n", something);
		ReleaseSemaphore(print_sem, 0, NULL);

		//////

		WaitForSingleObject(print_sem1, INFINITE);
		printf("Enter the string\n");
		fgets(buffer, SIZE, stdin);
		_tcscpy(string, A2T(buffer));
		CopyMemory((PVOID)buffer_pointer, string, (SIZE - 1 * sizeof(TCHAR)));
		ReleaseSemaphore(print_sem, 0, NULL);
	}
		Sleep(100000);

		UnmapViewOfFile(pBuf);
		UnmapViewOfFile(buffer_pointer);

		CloseHandle(file_handler);
		CloseHandle(hMapFile);

		return 0;
}
#endif
