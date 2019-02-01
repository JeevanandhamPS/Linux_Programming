/***************************************/
/* Author	: Jeevanandham.P.S     */
/* Date		: 30jan2019            */
/* Filename	: my_sem.h             */
/* Description	: header files         */
/***************************************/

#ifndef MY_SEM_H
#define MY_SEM_H


/* Included header files */

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <string.h>


/* Macro Definitions */

#define SEM_KEY 100
#define SHM_KEY 111
#define NSEMS   4
#define PERMISSION IPC_CREAT|0640
#define SHM_SIZE 8192


/* user defined datatype definitions */
union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *__buf;
};

#endif //MY_SEM_H
