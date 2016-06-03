#include "lib.h"
#ifdef linux
int8_t toggle = FALSE;
int count = 5;
struct aiocb cb;
char buffer[256];

void* thread_write(void* args)
{
	int cat_file = open("concatenated", O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (cat_file == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	while (count > 0)
	{
		while (FALSE == toggle)
		{
			usleep(100);
		}

		cb.aio_nbytes = strlen(buffer);
		cb.aio_fildes = cat_file;

		if (aio_write(&cb) == -1)
		{
			perror("aio_write");
			close(cat_file);
			exit(EXIT_FAILURE);
		}

		while (aio_error(&cb) == EINPROGRESS) {}
		toggle = FALSE;
	}

	printf("Data has been written\n");
	pthread_exit(NULL);
}

void* thread_read(void *args)
{
	char file_name[256];

	memset(&cb, 0, sizeof(cb));
	cb.aio_offset = 0;
	cb.aio_buf = buffer;

	for (int i = 1; i < 6; i++)
	{
		while (toggle == TRUE)
		{
			usleep(100);
		}

		sprintf(file_name, "%d", i);
		int current_file = open(file_name, O_RDONLY);

		if (current_file == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}

		cb.aio_nbytes = 256;
		cb.aio_fildes = current_file;

		if (aio_read(&cb) == -1)
		{
			perror("aio_read");
			close(current_file);
			exit(EXIT_FAILURE);
		}

		while (aio_error(&cb) == EINPROGRESS) {}

		count--;
		toggle = TRUE;
		printf("%s", buffer);
		close(current_file);
	}
	printf("Data has been readed\n");

	pthread_exit(NULL);
}
#endif



#ifdef _WIN32
#include "lib.h"

char file_readed[5] = { 0, 0, 0, 0, 0 };
char bytes_written = 0;
char* buffer;

DWORD WINAPI reader(CONST LPVOID lpParam)
{
	buffer = (char*)malloc(SIZE);
	printf("Reader thread\n");
	for (int i = 1; i < 6; i++)
	{
		char name[3];
		_itoa(i, name, 10);

		HANDLE file_handler = CreateFileA(name, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);

		if (file_handler == INVALID_HANDLE_VALUE)
		{
			perror("CreateFileA");
			exit(EXIT_FAILURE);
		}

		int read_size = 10;
		char* read_data = (char*)malloc(read_size);

		memset(read_data, 0, read_size);

		OVERLAPPED overlapped;

		memset(&overlapped, 0, sizeof(overlapped));

		BOOL result = ReadFile(file_handler, read_data, read_size, NULL, &overlapped);
		printf("%s\n", read_data);

		while (HasOverlappedIoCompleted(&overlapped) == FALSE)
		{
			Sleep(10);
		}

		strcpy(buffer, read_data);
		file_readed[i - 1]++;
		bytes_written += strlen(read_data);
		DWORD bytes_readed;
		result = GetOverlappedResult(file_handler, &overlapped, &bytes_readed, TRUE);
		Sleep(1000);
		CloseHandle(file_handler);
	}
	ExitThread(0);
}

DWORD WINAPI writer(CONST LPVOID lpParam)
{
	printf("Writer thread\n");

	HANDLE writer_file = CreateFileA("concatenated", FILE_ALL_ACCESS, 0, NULL, CREATE_ALWAYS, FILE_FLAG_OVERLAPPED, NULL);

	for (int i = 1; i <= 5; i++) {

		if (writer_file == INVALID_HANDLE_VALUE)
		{
			perror("CreateFileA");
			exit(EXIT_FAILURE);
		}

		DWORD file_pointer = SetFilePointer(writer_file, 0, NULL, FILE_END);
		int read_size = 10;
		char* write_data = (char*)calloc(1, read_size);

		while (0 == file_readed[i - 1])
		{
			Sleep(10);
		}

		strcpy(write_data, buffer);
		OVERLAPPED overlapped;
		memset(&overlapped, 0, sizeof(overlapped));
		DWORD length;
		GetFileSize(writer_file, &length);
		overlapped.Offset = file_pointer;

		BOOL result = WriteFile(writer_file, write_data, strlen(write_data), NULL, &overlapped);
		while (FALSE == HasOverlappedIoCompleted(&overlapped))
		{
			printf("Working");
		}

		file_readed[i - 1]++;
		DWORD bytes_readed;
		result = GetOverlappedResult(writer_file, &overlapped, &bytes_readed, TRUE);
	}
	CloseHandle(writer_file);
	ExitThread(0);
}
#endif
