#include "header.h"

#ifdef __linux__
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void print(char* thread_id/*, int*a*/)
{
  for(int i = 0; i < strlen(thread_id); i++)
    {
      printf("%c", thread_id[i]);
      fflush(stdout);
      usleep(SLEEP_TIME);
    }
 //   printf(", I am %d\n\r", *a);
  printf("\n\r");
  fflush(stdout);
}

void* thread_print(void* args)
{
  char thread_id[256];
  int cancel_state = 0;
  
  sprintf(thread_id, "My id is %ld", syscall(SYS_gettid));
  
  while(TRUE)
    {
            
      cancel_state = pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);

      if(0 != cancel_state)
	{
	  perror("setcancelstate");
	  exit(EXIT_FAILURE);
	}
      
      pthread_mutex_lock(&mutex);
      print(thread_id/*, (int*)args*/);
      pthread_mutex_unlock(&mutex);

      cancel_state = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

      if(0 != cancel_state)
	{
	  perror("setcancelstate");
	  exit(EXIT_FAILURE);
	}
      
      usleep(100);
    }
  
  pthread_exit(NULL);
}

int main()
{
  pthread_t thread[THREADS_NUMBER]; 
  
  int position = 0;

   	initscr();
 	nodelay(stdscr, TRUE);
  
  while(TRUE)
    {

 	char c = getchar();

    switch(c)
	{
	case '+':
	  {
	    if(position >= 10)
	      {
		printf("Thread list is full\n");
		break;
	      }
	    
	    pthread_create(&thread[position], NULL, &thread_print, NULL);
	    
	    position++;
	    
	    break;
	  }
	case '-':
	  {
	    if(position <= 0)
	      {
		printf("Unable to terminate...nothing?\n\r");
		break;
	      }
	    
	    pthread_cancel(thread[position - 1]);
	    pthread_join(thread[position - 1], NULL);
	    
	    position--;
	    
	    break;
	  }
	case 'q':
	  {
	    for (int i = 0; i < position; i++)
	      {
		pthread_cancel(thread[i]);
		// could be used to wait for threads end printing 
		pthread_join(thread[i], NULL); 
	      }
	    
	    exit(EXIT_SUCCESS);
	  }
	  
	}
    }
  
  return 0;
}

#endif



#ifdef _WIN32
HANDLE semaphore;
int a[5];
HANDLE thread;
unsigned long thread_id;

typedef struct Stack
{
	HANDLE value;
	struct Stack *next;
}Stack;

HANDLE pop(Stack **head);
void push(HANDLE value,Stack** head);

void Thread(void* pParams, Stack **head )
{ 
	int i, num = 0;
	while (TRUE)
	{ 
		int id = GetCurrentThreadId();

		WaitForSingleObject(semaphore, INFINITE);

		printf("My id is:%d\n", id);

		ReleaseSemaphore(semaphore, 1, NULL);
		Sleep(SLEEP_TIME);
	}
}

int main()
{ 
	TCHAR name[]=TEXT("Semaphore");
	semaphore = CreateSemaphore(NULL, 1, 1, name);
	char symbol;
	Stack *stack=NULL;

	while(TRUE)
	{
		symbol = getchar();
		if('+' == symbol)
		{
			thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread, NULL, 0, &thread_id);
			push(thread,&stack);
		}
		if('-' == symbol)
		{
			if(stack != NULL)
			{
				TerminateThread(pop(&stack),0);
			}
			else
			{
				puts("Thread stack is empty");
			}
		}
		if('q' == symbol)
		{
			while(NULL != stack)
			{
				TerminateThread(pop(&stack),0);
			}
			return 0;
		}
	}
	return 0;
}

void push(HANDLE value,Stack** head)
{
	Stack *temp =(Stack*) malloc(sizeof(Stack));	
	if(NULL == temp)
	{
		perror("push");
		exit(EXIT_FAILURE);
	}
	temp->next = *head;
	temp->value = value;
	*head = temp;
}

HANDLE pop(Stack **head)
{
	Stack *popped;
	HANDLE value;
	popped = *head;
	*head = (*head)->next;
	value = popped->value;
	free(popped);
	return value;
}
#endif
