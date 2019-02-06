/************************************************/
/* Author	: Jeevanandham.P.S     		*/
/* Date		: 6-feb-2019	       		*/
/* Filename	: mutex.c              		*/
/* Description	: thread working with mutex     */
/************************************************/

/* Included header file */
#include "mutex.h"

/* Global variable definitions */

int global = 0;

/* mutex is a variable type pthread_mutex_t */
static pthread_mutex_t mutx = PTHREAD_MUTEX_INITIALIZER;/* mutex should initialize as a static */


/* function definitions */

int main()
{
	int thread_create,thread_join,i;
	pthread_t thread1,thread2;  /* pthread_t variable */
	int arg = 10000000;

	/* Create a first thread and call the thread_fun with argument */
	thread_create = pthread_create(&thread1,NULL,thread_fun,&arg);
	perror("pthread_create");

	/* Create a second thread and call the thread_fun with argument */
	thread_create = pthread_create(&thread2,NULL,thread_fun,&arg);
	perror("pthread_create");

	/* join the first thread */
	thread_join = pthread_join(thread1,NULL);
	perror("pthread_join");

	/* join the second thread */
	thread_join = pthread_join(thread2,NULL);
	perror("pthread_join");

	/* Print the final global variable value */
	printf("global = %d\n",global);
}

void *thread_fun(void *ptr)
{
	int *addr = (int *)ptr;
	int local,i,mut;

	for(i=0;i<(*addr);i++)
	{
		/* pthread_mutex_lock is lock the thread if thread in unlock period otherwise it can wait */
		mut = pthread_mutex_lock(&mutx);
		local = global;
		local++;
		global = local;
		/* pthread_mutex_unlock is unlock the thread if thread in lock period, otherwise it can wait */
		mut = pthread_mutex_unlock(&mutx);
	}
}
