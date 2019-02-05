/***************************************/
/* Author	: Jeevanandham.P.S     */
/* Date		: 5-feb-2019	       */
/* Filename	: pthread.c            */
/* Description	: working of thread    */
/***************************************/

/* Included header file */
#include "pthread.h"

/* Global variable definitions */


/* function definitions */
int main()
{
	int thread_create,thread_join,*ptr;
	unsigned long long int in,inp1,inp;
	pthread_t thread;
	void *data;

	inp = 4294967295*5;

	inp1 = inp+inp;

	/*create a new thread by using pthread_create library call*/
	thread_create = pthread_create(&thread, NULL, fun_thread,&inp); /*third parameter is a function call, fourth one is an argument of the function*/
	perror("pthread_create");

	fun_thread(&inp1);
}

void *fun_thread(void *arg)
{
	unsigned long long int *sam = (unsigned long long int *)arg;
	unsigned long long int i,j=0;

	for(i=0;i<(*sam);i++)
	{
		j+=(i*i);
	}
	printf("%llu\n",j);

}
