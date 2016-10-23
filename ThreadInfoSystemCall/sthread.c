#include <limits.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "sthread.h"
#define PTHREAD_SYNC

pthread_mutex_t count_mutex;
pthread_barrier_t barr;
int SharedVariable = 0;

//This structure represents individual threads with the pthread_t and threadID
typedef struct {
	pthread_t thread;
	int threadID;
}TStruct;

int inputValidation(int argc, char*argv[])
{

int base;
char *endptr, *str;
long val;

     if (argc < 2)
      {
           fprintf(stderr, "Usage: %s str [base]\n", argv[0]);
           exit(EXIT_FAILURE);
      }

           str = argv[1];
           base = (argc > 2) ? atoi(argv[2]) : 10;

           errno = 0;    /* To distinguish success/failure after call */
           val = strtol(str, &endptr, base);

           /* Check for various possible errors */

           if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
                   || (errno != 0 && val == 0)) {
               perror("strtol");
               exit(EXIT_FAILURE);
           }

	  if (endptr == str) {
               fprintf(stderr, "No digits were found\n");
               exit(EXIT_FAILURE);
           }

           /* If we got here, strtol() successfully parsed a number */

           printf("strtol() returned %ld\n", val);

           if (*endptr != '\0')        /* Not necessarily an error... */
           {    printf("Further characters after number: %s\n", endptr);
		exit(EXIT_SUCCESS);
	   }
return val;
}

void* SimpleThread(void* th)
{
	//parameter converted back to struct object
	TStruct * ts = (TStruct*)th;
	int num, val;
	for(num = 0; num < 20; num++)
	{
		//PTHREAD_SYNC done to synchronize the threads
		#ifdef PTHREAD_SYNC
		//Locking SharedVariable so only one thread can manipulate it at a time.
		pthread_mutex_lock(&count_mutex);
		#endif

		//Locking SharedVariable so only one thread can manipulate it at a time.

		val = SharedVariable;
		printf("***thread %d sees value %d\n", ts->threadID , val);
		SharedVariable = val + 1;

		//Unlocking so next thread can do work 
		pthread_mutex_unlock(&count_mutex);

	}
	//Barrier done here to force threads to wait before finalizing to print at same time.
	pthread_barrier_wait(&barr);
	val = SharedVariable;
	printf("Thread %d sees final value %d\n",ts->threadID, val);
//	syscall(__NR_rive);
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	//User input is taken and stored
	inputValidation(argc, argv);

	int userinput = atoi(argv[1]);
	int i;
	TStruct *thr;//created a pointer type to the struct representing a thread

	//Initialize mutex variables
	pthread_mutex_init(&count_mutex, NULL);
	pthread_barrier_init(&barr,NULL, userinput);

	//Loop with userinput as limit to create threads
	for(i =0; i < userinput; i++)
	{
		//Memory is allocated for struct size of the thread
		thr = (TStruct*) malloc(sizeof(TStruct));
		thr->threadID = i; //Thread ID is the loop number upon which it was created
		pthread_create(&(thr->thread),NULL, SimpleThread,thr);

	}
	//System call called here
	syscall(__NR_rive);
	//Threads are joined
	for(i =0; i < userinput; i++)
	{
		pthread_join(thr->thread, NULL);
	}

	return 0;
}
