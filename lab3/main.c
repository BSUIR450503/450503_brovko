#include "header.h"

#ifdef __linux__
int main(int argc, char*argv[])
{
  sem_t* semafor = NULL;
  sem_t* semafor1 = NULL;

  int file_descriptor[2];
  int pipes[2];

  char write_buffer[256], read_buffer[256];

  semafor = sem_open("sem", O_CREAT, 0777, 1);
  semafor1 = sem_open("sem1", O_CREAT, 0777, 1);

  if(semafor == SEM_FAILED)
    {
      perror("sem_open");
      exit(-1);
    }
  
  if(sem_init(semafor, 0, 0) == -1)
    {
      perror("sem_init");
      exit(-1);
    }

    if(semafor1 == SEM_FAILED)
    {
      perror("sem_open");
      exit(-1);
    }
  
  if(sem_init(semafor1, 0, 0) == -1)
    {
      perror("sem_init");
      exit(-1);
    }
    
  if(pipe(file_descriptor) == -1)
    {
      perror("pipe");
      exit(-1);
    }

  if(pipe(pipes) == -1)
    {
      perror("pipe");
      exit(-1);
    }
    
      char value0[10], value1[10], value2[10], value3[10];
      sprintf(value0, "%d", file_descriptor[0]);
      sprintf(value1, "%d", file_descriptor[1]);
      sprintf(value2, "%d", pipes[0]);
      sprintf(value3, "%d", pipes[1]);
      usleep(1000);
  
  pid_t p = fork();

  switch(p)
    {
    case -1:
      {
	perror("fork");
	exit(-1);
      }
    case 0:
      {
      
   execlp ("/usr/bin/xterm", "xterm", "-bd", "black", "-bg", "black",
           "-fg", "green", "-geometry", "100x20+400+400", "-T", "child", "-e",
          "/home/tatiana/Загрузки/3/3/child",
          "sem", "sem1", value0, value1, value2, value3, (char *)0);
	break;
      }
      
    default:
      {
	int32_t parent_semafor;
  	int32_t parent_semafor1;
	close(file_descriptor[0]);
 	close(pipes[1]);

	while(TRUE)
	  	{
		sem_getvalue(semafor1, &parent_semafor1);
   		 if(parent_semafor1 == 0)
   		 	{
  			read(pipes[0], read_buffer, sizeof(read_buffer));
   			printf("The transmitted string: %s", read_buffer);
    		if (read_buffer[0] == '/') {
    		sem_close(semafor);
      		sem_close(semafor1);
      		exit(0);
    	  	}
      	} 

	    sem_getvalue(semafor, &parent_semafor);
	    if(0 == parent_semafor )
	      {
          sem_post(semafor);
		printf("Enter the string\n");
		fgets(write_buffer, sizeof(write_buffer), stdin);
		printf("Ready to transmit\n");
		write(file_descriptor[1], write_buffer, strlen(write_buffer) + 1);
		printf("The string has been sent\n");
		sem_trywait(semafor);
}
	  }
	waitpid(p, NULL, 0);
	exit(0);
	
	break;
      }
    }
  
  return 0;
}
#endif



#ifdef _WIN32
TCHAR file_name[] = TEXT("Local\\mapfile");
TCHAR szName[] = TEXT("Local\\mapfile1");

int main()
{
	HANDLE file_handler;
	LPCTSTR buffer_pointer;

	TCHAR string[SIZE];
	char buffer[SIZE];
	///
	HANDLE hMapFile;
	LPCTSTR pBuf;
	LPSTR lpszAscii = NULL;
	///
	volatile HANDLE sem, print_sem, sem1, print_sem1;

	sem = CreateSemaphore(NULL, 0, 1, L"SEMAFOR");
	print_sem = OpenSemaphore(SYNCHRONIZE, TRUE, L"SEMAWHILE");

	sem1 = OpenSemaphore(SYNCHRONIZE, TRUE, L"SEMAWHILE1");
	print_sem1 = CreateSemaphore(NULL, 0, 1, L"SEMAFOR1");

	file_handler = CreateFileMapping(
		INVALID_HANDLE_VALUE,
		NULL,
		PAGE_READWRITE,
		0,
		SIZE,
		file_name
		);

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
		szName
		);


	if (NULL == file_handler)
	{
		perror("CreateFileMapping");
		return -1;
	}

	buffer_pointer = (LPTSTR)MapViewOfFile(
		file_handler,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		SIZE
		);

	if (NULL == buffer_pointer)
	{
		perror("MapViewMapping");
		CloseHandle(file_handler);
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

	USES_CONVERSION;

	while (TRUE)
	{
		WaitForSingleObject(print_sem, INFINITE);
		printf("Enter the string\n");
		fgets(buffer, SIZE, stdin);
		_tcscpy(string, A2T(buffer));
		CopyMemory((PVOID)buffer_pointer, string, (SIZE - 1 * sizeof(TCHAR)));
		ReleaseSemaphore(sem, 1, NULL);

		////////

		WaitForSingleObject(sem1, INFINITE);
		lpszAscii = T2A((LPTSTR)pBuf);
		int len = strlen(lpszAscii);
		char something[256];
		strcpy(something, lpszAscii);
		printf("I got %s\n", something);
		ReleaseSemaphore(print_sem1, 1, NULL);

	}

	Sleep(1000000000);

	UnmapViewOfFile(buffer_pointer);
	UnmapViewOfFile(pBuf);

	CloseHandle(file_handler);
	CloseHandle(hMapFile);

	return 0;
}
#endif