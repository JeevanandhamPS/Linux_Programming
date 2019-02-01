/***************************************/
/* Author	: Jeevanandham.P.S     */
/* Date		: 30jan2019 	       */
/* Filename	: my_sem2.c            */
/* Description	: semaphore            */
/***************************************/

/* Included header file */
#include "my_sem2.h"

/* Global variable definitions */


/* function definitions */

int main()
{
	int semid,semctl_,shmid,semop_;
	char *shm_addr;

	union semun sem_union1;
	struct sembuf my_sembuf;
	
	/* semaphore creation with MY_SEMKEY as key */
	semid = semget(SEM_KEY, NSEMS,0);

	/* error msg */
	perror("semget");

	/* create a shared memory */
	shmid = shmget(SHM_KEY, SHM_SIZE,0);

	/* error message */
	perror("shmget");

	/* To get a virtual address */
	shm_addr = shmat(shmid, NULL, 0);

	/* error message */
	perror("shmat");

	/* Assign values tom the "union semun" */
	sem_union1.val = 3;

	/* semaphore control*/
	semctl_ = semctl(semid, 0, SETVAL, sem_union1);

	/* error message */
	perror("semctl");
	
	/* semaphore number to my_sembuf.sem_num*/
	my_sembuf.sem_num = 0;

	/* Reduce one */
	my_sembuf.sem_op = -1;
	
	/* assign SEM_UNDO it defined in sem.h */
	my_sembuf.sem_flg = SEM_UNDO;

	printf("Waiting for semaphore lock\n");
	sleep(5);

	/* set the values to operate the semaphore*/
	semop_ = semop(semid,&my_sembuf,1);

	/* error msg */
	perror("semop");

	printf("Semaphore locked\n");
	sleep(5);

	printf("Entering critical area\n");

	/*reading process*/
	printf("%s\n",shm_addr);
	sleep(5);

	printf("Exiting the critical area\n");

	/* clear the value to reach a 0 */
	my_sembuf.sem_op = 1;

	my_sembuf.sem_flg = 0;

	sleep(5);

	printf("Lock released\n");


	/* Update the semaphore operation */
	semop_ = semop(semid, &my_sembuf, 1);

	/*error msg*/
	perror("semop");
	sleep(5);

	shmdt(shm_addr);
	perror("shmdt");

	return 0;
}

